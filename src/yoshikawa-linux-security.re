= AmazonLinuxでも使える！auditdによるLinuxセキュリティ強化術

== はじめに
Linux には標準で導入されているセキュリティ機能が数多くあり、その中の一つに auditd が有ります。
audit という単語が示す通り、監査機能を提供するプログラムです。@<br>{}

そもそも監査って何…？という話について、詳細は割愛しますが
要はシステムがどのように使われたかを記録し、必要な時にそれを参照できるようにする仕組みです。@<br>{}

普段サーバーの稼働中にはプログラムの起動やユーザーのログインなど、様々なイベントが発生します。
これらは普段から全てを把握しておく必要性は薄いものの、有事の際にはその内容を確認し
実際に何が起きたのかを正確に把握する必要があります。@<br>{}

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
せっかく準備されているものを腐らせておくのはとてももったいないので、有効活用しましょう。@<br>{}

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
auditd による監査機能は複数のプログラム・ツールから成り立っています。
まずはどんなものがあるのかザッと見てみましょう。

=== auditd / kauditd
システム起動時に起動・常駐し、システムの挙動を監視する auditd 本体とも言えるデーモンです。
再起動等は systemd、設定等は後述の auditctl で操作するので、直接触ることはほぼありません。@<br>{}

auditd がユーザースペースプロセス、kauditd がカーネルスペースのプロセスです。
それぞれ役割が異なりますが、本稿では 2 つまとめて auditd として扱います。

//comment{
==== コラム：カーネルスペースとユーザースペース
(ページ数が足りなそうなら書く…？)
//}

=== auditctl
auditd の管理を行うコマンドです。systemd と systemctl のような関係ですね。
auditd の操作で一番多く触ることになるプログラムです。

=== ausearch
auditd で記録された監査ログはテキスト形式ではあるものの、そのまま人間が読むのは少々（かなり？）辛いものが有ります。
ausearch は監査ログから指定した条件を満たすログを抽出し、人間が読みやすい形で表示する事ができます。

=== aureport
auditd によって生成された監査ログからレポートを生成します。

=== /etc/audit/audit.conf
auditd のメイン設定ファイルです。auditd 自身の設定や、
どんなシステムの挙動を記録するのかという監査ルールをこのファイルで設定します。
ただし、直接編集することは有りません。auditctl で設定した内容が書き込まれます。

=== /etc/audit/audit.rules
auditd の起動時に読み込まれるルールが保存されているファイルです。
ファイルの冒頭にコメントが記載してありますが、このファイルは /etc/audit/audit.d/ にある
*.rules ファイルをもとにして augenrules コマンドで生成されます。

=== /var/log/audit
auditd によって記録されたログが格納されます。
ただし ausearch の項でも触れましたが、記録されるログはテキストではあるものの
人間には非常に読みづらいため、ausearch を使ってログを閲覧します。

== auditd の基本操作

=== 利用準備

==== インストール
基本的に不要です。
AWS から提供されている Amazon Linux の AMI で起動したインスタンスには導入済み。
CentOS7 公式 AMI も同様です。
仮に CentOS7 を VM などに自分で最小構成インストールしたとしてもインストールされます。
つまり、あえて意図的に無効化しない限り最初から使える環境にあるということです。@<br>{}

もし万が一、利用中の環境にインストールされていないようなら以下のコマンドでインストールすることができます。

//list[auditctl-install][audit パッケージのインストール]{
# yum install audit
//}

==== サーバー起動時の自動起動
これも不要です。最初からシステム起動時に auditd も起動するようになっています。
Amazon Linux 1 では chkconfig、Amazon Linux 2 や CeontOS7 では systemd で制御されています。

==== auditd の起動・停止・設定の再読み込み
CentOS6 では service コマンドで(再)起動や停止を行えます。
CentOS7 や Amazon Linux 2 環境は systemctl で…と言いたいところなのですが、
実は RedHat のマニュアルに systemctl ではなく service で行う必要があると記載が有ります@<fn>{audit-rhel-manual}。
ここは他のソフトウェアと異なる点なので、注意が必要です。

//footnote[audit-rhel-manual][https://access.redhat.com/documentation/ja-jp/red_hat_enterprise_linux/7/html/security_guide/sec-starting_the_audit_service]

==== 必要な権限について
auditd の操作は全て root 権限が必要です。
その為、本稿では特に記載がない限り root ユーザーで操作している前提とします。
環境によって sudo をコマンドの前につける等して root 権限で各コマンドを実行してください。

=== 現在の監査ルールの確認
auditctl -l で現在の設定を表示することができます。

//list[auditctl-list][auditctl -l によるルールの表示]{
# auditctl -l
No rules
//}

デフォルトではこのように監査ルールが何も設定されていない状態で稼働しているため、
ルールがない旨の表示がでます。

=== auditd 自体の設定表示
auditctl -s で auditd 自体の設定を表示できます。

//list[auditctl-setting][auditctl -s による設定の表示]{
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

各項目はそれぞれ以下のような意味を持ちます。

//table[auditctl-setting][ルール追加時の auditctl オプション]{
.	効果
-------------
enabled	audit が有効かどうかを示します。
failure	.
pid	.
rate_limit	.
backlog_limit	.
lost	.
backlog	.
loginuid_immutable 0 unlocked	.
//}

== ルールの追加
ルールの追加は auditctl コマンドを利用して行います。
例として /tmp/test.txt というファイルが作成されたり、
内容に変更が有ったら記録するファイルシステム監査のルールを設定してみます。

//list[auditctl-add][ルールの追加]{
auditctl -f
//}

エラーが出なければルールの追加ができています。確認してみます。

//list[auditctl-list2][追加したルールの確認]{
auditctl -l

TODO: aaaaaaaaaaaaaaaaaaaaaa
//}

追加時のオプションはそれぞれ以下のような意味を持ちます。
詳細は man auditctl や RedHat が提供しているマニュアルページを参照してください。

//table[auditctl-option-table][ルール追加時の auditctl オプション]{
.	効果
-------------
-l	現在のルールを表示します
//}

== ログの確認
これで /tmp/test.txt が作成されたり変更があった際に記録されるようになりました。
実際にファイルを作成してみて、それが記録されていることを確認してみましょう。

//list[ausearch][テストファイルの作成と ausearch の実行]{
echo "TEST" >> /tmp/text.txt
ausearch
//}

ausearch を実行すると以下のような内容が表示されます。

//list[ausearch-result][ausearch の実行結果]{
echo "TEST" >> /tmp/text.txt
ausearch
//}

== ルールの削除
ルールの削除も auditctl で行います。

//list[auditctl-delete][ルールの削除]{
auditctl -f
//}

== ssh ログイン監査の設定事例
auditd を利用して、システムに ssh でログインされた記録を取り、
ログインが検知されたらメールで通知するようにしてみましょう。

=== ssh のログイン検知の仕組み
ssh によるログインが発生した際には必ず xxxx システムコールが発行されて tty が割り当てられます。
このシステムコールの実行を auditd で追跡・記録する事で ssh によるログインを検知する事ができます。

=== 監査ルールの追加
auditctl を使って、システムコールの監査ルールを追加します。

//list[audit-ssh-add-rule][システムコールの監査ルールを追加]{
auditctl -f
//}

エラーが出なければルールの追加に成功していますが、念の為確認します。

//list[audit-ssh-list-rule][追加したルールの確認]{
auditctl -l

TODO: aaaaaaaaaaaaaaaaaaaaaa
//}

=== メール送信の設定
ssh によるログインが行われ、auditd が検知したらメールを送信するように設定します。
なお、事前にこのシステムからメールが送信できるよう postfix 等の設定をしておいてください。

== まとめ
この章では auditd による監査機能の概要と基本設定の一部をご紹介しました。
本稿で紹介した内容は auditd 入門編ともいうべき最も基礎的な内容ではあるものの、
ここまで理解できれば後はどのような項目を監査するのかを考える事が大半を占めます。@<br>{}

是非まずは本稿で示した例を試して感覚を掴み、その後
自分が管理するシステムに合わせて auditd を活用できるよう、
どんどんルールの追加を試してみてください。

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