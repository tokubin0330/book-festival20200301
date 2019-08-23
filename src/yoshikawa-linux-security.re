= 令和から始める AmazonLinux で使えるセキュリティ強化術 (auditd 導入編)

== はじめに
Linux には標準で導入されているセキュリティ機能が数多くあり、その中の一つに auditd が有ります。
audit という単語が示す通り、監査機能を提供するプログラムです。
そもそも監査って何…？という話について、詳細は割愛しますが
要はシステムがどのように使われたかを記録し、必要な時にそれを参照できるようにする仕組みです。@<br>{}

普段サーバーの稼働中にはプログラムの起動やユーザーのログインなど、様々なイベントが発生します。
これらは普段から全てを把握しておく必要性は薄いものの、有事の際にはその内容を確認し
実際に何が起きたのかを正確に把握する必要があります。
事象を正確に把握できなければ、起きていることの把握や説明もできず、当然それへの対策案も考えられません。
auditd による監査機能はこのような時に備えて準備しておく、いわばセキュリティの屋台骨です。@<br>{}

今後はコンテナやサーバーレスといった環境が主流となっていくのかもしれませんが、
それでも Linux サーバーの管理が無くなることはなく、そのセキュリティ対策も必要な状況が続きます。
本稿では auditd を利用して Linux のセキュリティを少し向上させる方法をお伝えしたいと思います。

== 対象の読者と環境
ターミナルによる Linux の基本的な操作は理解されている前提とさせて頂きます。
また、以下の環境で動作確認をしています。

 * Amazon Linux
 * Amazon Linux 2
 * CentOS7

なお、余談ですが auditd を利用した監査設定は
LPIC / LinuC Level3 303 Security 試験の主題の一つです。
この試験の受験を考えている方にとっても一定のお役に立てるのではないかと思います。

== auditd の概要
前述したとおり、標準で導入されている監査ツールです。
しかし、デフォルトでは何も設定がされておらず、監査の役に立つ状態ではありません。
せっかく準備されているものを腐らせておくのはとてももったいないので、有効活用しましょう。
auditd では監査の内容として「ファイルシステムの監査」「システムコールの監査」の 2 つを設定できます。

=== ファイルシステムの監査
ファイル自体の変更、パーミッションの変更はもちろんの事、読み取りアクセスも監視・記録することが可能です。
/etc/passwd など、変更があった場合にチェックしておきたいファイルについて設定を行います。

=== システムコールの監査
kernel に送られてきたシステムコールを監視・記録することが可能です。
とはいえ、システムコールは常に利用されている物で種類も膨大な為、すべてを記録する事はナンセンスです。
普段呼び出されない、または人間の操作によって呼び出されるであろうシステムコールを監査する辺りが
ちょうどよいレベル感ではないかと個人的には考えています。

== auditd を構成するプログラム・ファイル
auditd による監査機能は複数のプログラムやファイルから成り立っています。
まずはどんなものがあるのかザッと見てみましょう。

==== auditd & kauditd
システム起動時に起動・常駐し、システムの挙動を監視する auditd 本体とも言えるデーモンです。
再起動等は service コマンド、設定等は後述の auditctl で操作するので、直接触ることはほぼありません。
auditd がユーザースペースプロセス、kauditd がカーネルスペースのプロセスです。
それぞれ役割が異なりますが、本稿では 2 つまとめて auditd として扱います。

//comment{
==== コラム：カーネルスペースとユーザースペース
(ページ数が足りなそうなら書く…？)
//}

==== auditctl
auditd の管理を行うコマンドです。systemd と systemctl のような関係ですね。
auditd の操作で一番多く触ることになるプログラムです。

==== ausearch
auditd で記録された監査ログから指定した条件を満たすログを抽出・表示します。
時刻やユーザー名等を人間が読みやすい形で表示する事もできます。

==== aureport
auditd によって生成された監査ログからレポートを生成します。

==== /etc/audit/auditd.conf
auditd 自身の設定ファイルです。
監査ログの場所やローテート方式等を設定します。

==== /etc/audit/audit.rules & augenrules
auditd の起動時に読み込まれるルールが保存されているファイルです。
ファイルの冒頭にコメントが記載してありますが、このファイルは /etc/audit/audit.d/ にある
*.rules ファイルをもとにして augenrules コマンドで生成されます。

==== /var/log/audit
auditd によって記録されたログが格納されるデフォルトの場所です。
ただし、記録されるログはテキストではあるものの人間には少々読みづらいため、
通常は ausearch を使ってログを閲覧します。

== auditd の基本操作

=== 利用準備

==== インストール
基本的に不要です。
AWS から提供されている Amazon Linux の AMI で起動したインスタンスには導入済み。
CentOS7 公式 AMI も同様です。
仮に CentOS7 を VM などに自分で最小構成インストールしたとしてもインストールされます。
つまり、あえて意図的に無効化しない限り最初から使える環境にあるということです。
もし万が一、利用中の環境にインストールされていないようなら以下のコマンドでインストールすることができます。

//cmd{
# yum install audit
//}

==== サーバー起動時の自動起動
これも不要です。最初からシステム起動時に auditd も起動するようになっています。
Amazon Linux 1 では chkconfig、Amazon Linux 2 や CeontOS7 では systemd で制御されています。

==== auditd の起動・停止・設定の再読み込み
CentOS6 では service コマンドで(再)起動や停止を行えます。
CentOS7 や Amazon Linux 2 環境は systemctl で…と言いたいところなのですが、
実は RedHat のセキュリティガイドに systemctl ではなく service で行う必要があると記載が有ります@<fn>{audit-rhel-manual}。@<br>{}

ただし筆者が手元で CentOS7 や Amazon Linux 2 環境で試した限りでは service コマンドをたたいても結局 systemctl にリダイレクトされます。
この辺りかなりモヤっとするのですが、念のため service コマンドで操作することを推奨しておきます。
（正確な理由や推奨方法をご存じの方がいらっしゃったら教えてください…）

//footnote[audit-rhel-manual][https://access.redhat.com/documentation/ja-jp/red_hat_enterprise_linux/7/html/security_guide/sec-starting_the_audit_service]

==== 必要な権限について
auditd の操作は全て root 権限が必要です。
その為、本稿では特に記載がない限り root ユーザーで操作している前提とします。
環境によって sudo をコマンドの前につける等して root 権限で各コマンドを実行してください。

=== 現在の監査ルールの確認
auditctl -l で現在の設定を表示することができます。

//cmd{
# auditctl -l
No rules
//}

デフォルトでは監査ルールが何も設定されていない状態で稼働しているため、
このようにルールがない旨の表示がでます。

=== audit の挙動（制御ルール）の表示
auditctl -s で audit 自体の挙動を指定する「制御ルール」を表示できます。

//cmd{
# auditctl -s
enabled 1
failure 1
pid 396
rate_limit 0
backlog_limit 8192
lost 0
backlog 0
loginuid_immutable 0 unlocked
//}

主要な項目の意味を@<table>{auditctl-setting}に示します。

//tsize[20,100]
//table[auditctl-setting][auditd 制御ルール項目]{
.	効果
-------------
enabled	audit が有効かどうかを示します。@<br>{}0:無効、1:有効、2:設定変更不可（ロック）
failure	auditd が止まってしまうような重大なエラーが発生した場合の挙動を示します。@<br>{}0:何もしない、1:ログ出力、2:カーネルパニックを発生させる
rate_limit	1秒当たりのログ生成数を示します。0は無制限。
backlog_limit	カーネルにおける audit バッファの最大値を示します。
lost	カーネル内キューのオーバーフロー等によりロストしてしまったイベントの数を示します。
backlog	カーネル内キューに残っているイベントの数を示します。
//}

=== auditctl コマンドによる一時的なルールの追加
auditctl コマンドを利用してルールの追加を行ってみます。
例として /tmp/text.txt ファイルで書き込みや属性の変更が発生したらログに記録されるよう
ファイルシステムの監査ルールを設定してみます。
なお「一時的な」と書いてある通り、auditctl コマンドで追加したルールは再起動後に消えてしまいます。
再起動後も保持できるようにする方法は後述します。

//cmd{
# auditctl -w /tmp/test/txt -p wa -k testrule1
//}

エラーが出なければルールの追加ができています。確認してみます。

//cmd{
# auditctl -l
-w /tmp/test/txt -p wa -k testrule1
//}

追加時のオプションはそれぞれ以下のような意味を持ちます。
詳細は man auditctl や RedHat が提供しているマニュアルページを参照してください。

//tsize[20,100]
//table[auditctl-option-table][ファイルシステムルール追加時の auditctl オプション]{
オプション	意味
-------------
-w	監査対象のファイルを指定します。
-p	対象ファイルに対するどの動作をログに記録するか指定します。@<br>{}r:読み取り、w:書き込み、x:実行、a:属性変更
-k	このルールにつける任意の名前（キー）を指定します。
//}

==== ログの確認
これで /tmp/test.txt に変更があったら audit によってログが記録されるようになりました。
実際にファイルを少しいじってみて、その操作が記録されていることを確認してみましょう。

//cmd{
# echo "TEST" >> /tmp/test.txt
//}

今の操作がちゃんと記録されているか確認してみましょう。確認には ausearch コマンドを使います。

//cmd{
#ausearch -i -k testrule1
----
type=PROCTITLE msg=audit(08/23/2019 14:58:37.791:977) : proctitle=-bash
type=PATH msg=audit(08/23/2019 14:58:37.791:977) : item=1 name=/tmp/test.txt ino
de=67805551 dev=08:01 mode=file,644 ouid=root ogid=root rdev=00:00 obj=unconfine
d_u:object_r:user_tmp_t:s0 objtype=CREATE cap_fp=none cap_fi=none cap_fe=0 cap_f
ver=0
type=PATH msg=audit(08/23/2019 14:58:37.791:977) : item=0 name=/tmp/ inode=67149
893 dev=08:01 mode=dir,sticky,777 ouid=root ogid=root rdev=00:00 obj=system_u:ob
ject_r:tmp_t:s0 objtype=PARENT cap_fp=none cap_fi=none cap_fe=0 cap_fver=0
type=CWD msg=audit(08/23/2019 14:58:37.791:977) :  cwd=/etc/audit/rules.d
type=SYSCALL msg=audit(08/23/2019 14:58:37.791:977) : arch=x86_64 syscall=open s
uccess=yes exit=3 a0=0xeced90 a1=O_WRONLY|O_CREAT|O_APPEND a2=0666 a3=0xfffffff0
 items=2 ppid=3991 pid=3992 auid=vagrant uid=root gid=root euid=root suid=root f
suid=root egid=root sgid=root fsgid=root tty=pts1 ses=5 comm=bash exe=/usr/bin/b
ash subj=unconfined_u:unconfined_r:unconfined_t:s0-s0:c0.c1023 key=testrule1
//}

イベントはハイフンのみの行 (----) で区切られており、一つのイベントは複数行のログを含みます。
各行のログは type= から始まっていて、いつ・誰が・どんなコマンドを使って何を変更したのかがログから読み取れます。@<br>{}

-i オプションをつけると audit.log の記録内容を人間が理解しやすいものに置き換えて表示してくれます。
（UNIXTIME を通常の時刻表記にするなど。）

-k オプションでルールにつけたキーを指定することで、そのキーに関連するログを抽出しています。@<br>{}

ログの各項目について理解するために、まずは RedHat セキュリティガイドの
説明ページ@<fn>{audit-rhel-manual2}を一通り眺めてみる事をお勧めします。

//footnote[audit-rhel-manual2][https://access.redhat.com/documentation/ja-jp/red_hat_enterprise_linux/7/html/security_guide/sec-understanding_audit_log_files]

=== augenrules スクリプトによるルールの永続化
前述の通り auditctl で追加したルールは一時的なものであり、システムや auditd を再起動すると消えてしまいます。
再起動後もルールを保持するには起動時に読み込まれる /etc/audit/audit.rules ファイルにルールを加えます。

ただし、/etc/audit/audit.rules ファイルは直接編集しても意味が有りません。
このファイル自体が再起動時に毎回自動生成されているためです。
/etc/audit/rules.d/*.rules が再生成時の元ネタになりますので、ここにファイルを追加します。
ルールの数が少なければ /etc/audit/rules.d/audit.rules ファイルに追記してもいいです。（お行儀がよくないですが…）

なお、ファイル記載時の文法は auditctl に付与するオプションをそのまま書けば大丈夫です。
つまりは auditctl -l で出力されたものをそのままコピペです。@<br>{}

ファイルを置いたら augenrules を実行します。
--load オプションをつけることで、/etc/audit/audit.rules ファイルの再生成と読み込みを一度に行ってくれます。

//cmd{
# augenrules --load
/sbin/augenrules: No change
No rules
enabled 1
failure 1
pid 4167
rate_limit 0
backlog_limit 8192
lost 0
backlog 1
enabled 1
failure 1
pid 4167
rate_limit 0
backlog_limit 8192
lost 0
backlog 1
//}

ルールを新規追加する際にはまず auditctl で追加してみてエラーがないか確認し、
問題無ければ auditctl -l でリストを出力してそれをファイルに転記するのが個人的にはお勧めです。

//comment{
== ssh ログイン監査の設定事例
auditd を利用して、システムに ssh でログインされた記録を取り、
ログインが検知されたらメールで通知するようにしてみましょう。

=== ssh のログイン検知の仕組み
ssh によるログインが発生した際には必ず xxxx システムコールが発行されて tty が割り当てられます。
このシステムコールの実行を auditd で追跡・記録する事で ssh によるログインを検知する事ができます。

=== 監査ルールの追加
auditctl を使って、システムコールの監査ルールを追加します。
エラーが出なければルールの追加に成功していますが、念の為確認します。

=== メール送信の設定
ssh によるログインが行われ、auditd が検知したらメールを送信するように設定します。
なお、事前にこのシステムからメールが送信できるよう postfix 等の設定をしておいてください。
//}

== サンプルルールについて
audit パッケージにはサンプルのルールファイルが含まれており、
これを利用することで様々な認証基準に準拠した監査を比較的簡単に始めることができます。

//cmd{
# cd /usr/share/doc/audit-2.8.1/rules/
# ls
10-base-config.rules    23-ignore-filesystems.rules  42-injection.rules
10-no-audit.rules       30-nispom.rules              43-module-load.rules
11-loginuid.rules       30-pci-dss-v31.rules         70-einval.rules
12-cont-fail.rules      30-stig.rules                71-networking.rules
12-ignore-error.rules   31-privileged.rules          99-finalize.rules
20-dont-audit.rules     32-power-abuse.rules         README-rules
21-no32bit.rules        40-local.rules
22-ignore-chrony.rules  41-containers.rules
//}

例えば PCIDSS V3.1 に準拠した監査を行う必要がある場合は
10-base-config.rules、30-pci-dss-v31.rules、99-finalize.rules を /etc/audit/rules.d/ にコピーして
augenrules を実行する、といった形になります。@<br>{}

各ルールの冒頭に依存するルールや利用方法が書いてあるのと、
README-rules ファイルにもこれらのルールの利用方法が書いてあります。
サンプルルールを利用する場合はしっかり読みましょう。

== まとめ
この章では auditd による監査機能の概要と導入部分をご紹介しました。@<br>{}

ここで紹介した内容は auditd を使い始めるにあたって最も入門・基礎的な内容ではあるものの、
ここまで理解できれば後はどのような項目を監査するのか考える事、
特定のイベントが記録された際の対応を決める事、そしてそれらを実装していく事を繰り返すだけです。@<br>{}

本稿で auditd に関する概要を掴んで頂き、
自分が管理するシステムに合わせて auditd の活用を検討いただければ幸いです。



//comment{
=== 他にもこんなことができるよ

== ボリュームによってはここまででもいいかも…

== pam_pwquality
=== pam_pwquality の概要
=== 設定項目
=== 設定事例

== ACL
=== ACLの概要
=== ACLの基本操作
=== 「特定のグループのみ読み取り不可」の設定事例
//}