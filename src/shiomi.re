= AWS CI/CD入門
　皆さん、CI/CDしてますか？
今や開発において当たり前になった CI/CD。
当たり前になった反面プロジェクトアサイン時から CI/CD が組み込まれていたりで、よく理解しないまま何気なく利用している人もいるのではないかと思います。
また、新しい CI/CD ツールに載せ替えしたりすることもあるのではないかと思います。

そのような環境の人のためにこの章では、もう一度 CI/CD の基礎を学び直せるように CI/CD 基礎から
プロジェクトでよくある CI/CD の構成テンプレートを載せております。
お役に立てていただければ幸いです。



== CI/CDとは
　CI/CD という言葉は今や IT 業界では一般的になっており、CI/CDが何を示しているのかを説明する機会が減ってきています。
またプロジェクト毎や会社毎または、個人の認識の違いで CI/CD が取りうる範囲が少し違うこともしばしばあります。
ここではなるべくそういった言葉の齟齬をなるべくなくすために CI/CD が取り扱う範囲を定義します。

 CI/CD は英語では「Continuous Integration/Continuous Delevary」日本語に訳すと「継続的インテグレーション/継続的デリバリー」といいます。
　ここで 「CD にデプロイは入らないの？」と疑問に思った方のために RedHat が定義する CI/CD を参考@<fn>{redhat}にここでしっかりと言葉の定義をしていきます。

//footnote[redhat][CI/CD とは　https://www.redhat.com/ja/topics/devops/what-is-ci-cd#]

=== 継続的インテグレーション（Continuous Integration）
　継続的インテグレーション（以下 CI と呼ぶ）は主に開発メンバーのための開発プロセスの自動化を意味します。
開発メンバーが開発時にバグの無いコードを継続的に開発していくために、コードの解析やコードフォーマットの準拠
Unit テストなどを開発プロセスに自動で行うように組み込むことで品質を上げつつ開発効率を上げていくことを目的とします。
#@# 参照 CI/CD全体の範囲図
CI は最終的にプロジェクトで利用している共通のレポジトリに自動で統合されるところまでを行います。
こうすることで新しいコードの変更が自動で、コミット、ビルド、テストされ、バグの含みにくい開発プロセスが実施できます。
#@# マージ日に一括マージしている図がで機能開発が終わる毎にマージしている様子がの図


=== 継続的デリバリー（Continuous Delibary）
　継続的デリバリー（以下 CD と呼ぶ）は主に開発コードにバグがないか自動的にテストを行い、レポジトリにアップロードするまでの一連のプロセスの自動化を意味します。

#@# 参照 CI/CD全体の範囲図

CI の時と違う点は、CD がコードを最終的にアップロードする先が本番環境へデプロイされるために用意されたレポジトリである点です。
このレポジトリは常に本番環境がリリースできる状態のコードを保管しておくことが重要です。
また、継続的デリバリーのデリバリーが意味するところは、「本番相当の環境へデリバリーする」つまりシステムテストができる環境（ステージングと呼ばれたりする）にコードをデリバリーするところまでを指します。
したがって、その先のシステムテストに関しては CD のとりうる範囲ではありません。
システムテストを手動でテストするか自動でテストするかはプロジェクト要件次第になります。

CD は開発と運用のコミュニケーションロスを解決し、変更コードの導入作業の負担を下げることを目的としています。
本番環境へデプロイする運用者は CD によってアップロードされた最終的なソースコードが保管されているレポジトリさえ確認すれば開発者の変更コードを本番環境へデプロイすることができます。


=== 継続的デプロイメント
　継続的デプロイメント（以下 CD（deployment）と呼ぶ）はズバリ、本番環境にデプロイするまでのプロセスの自動化を意味します。
つまり、開発者の変更コードが全て自動で本番環境へデプロイされることを指します。
したがって、CD（deployment）の重要な本質は本番環境へ自動デプロイするためのシステムテストや UI テストなどの一連のテスト作業の自動化プロセスにあります。
筆者もデプロイまでを完全自動化で運用しているサービスにはまだ出会ったことがありません。
CD（deployment）を実現させるには事前のシステムテストの洗い出しや、システムテストの自動化、UIテストの自動化などを入念に設計しておかなければなりません。
しかし、これらが実現できるプロダクトではサービスのフィードバックを即座にコードに反映させビルド、テスト、デプロイをスピーディーかつ安全に本番環境へデプロイすることができるようになります。
時には、変更コードを少しずつアップデートし、デプロイメントによる障害のリスクを低減させることも可能になります。

本章ではこのCD（deployment）のためのテストの自動化に関しては取り扱いません。
システムテストや、UI テストはステージ環境で手動で実施することを前提として CI/CD を解説していきます。
また、次の項からお話する「本番環境のデプロイ」に関しては CD（deployment）の本質を意味する「システムテストの自動化」の意味合いを含めず単に本番環境へデプロイするための自動化プロセスのことを指し示すこととします。

#@# 図 CI/CD全体の範囲図

最後の CD（deployment）に関してはプロジェクトや会社ごとで認識はバラバラだと思うのでここでは混乱を防ぐために上記のような定義でお話していきます。

CI/CD を設計する上で大切なのは CI/CD はプロジェクトによってその自動化プロセスを自由に定義し、どこまで自動化するかを決めることができることです。
開発効率を高めるためにプロジェクトの規模と期間にあった自動化プロセスの定義をプロジェクト毎に都度設計していく必要があります。
本章ではそのような環境に置かれている開発者のお手伝いとなれるように私が過去に関わったことのある CI/CD のプロセスの事例について紹介していきます。


== The Twelve-Factor App に沿った CI/CD
　ソフトウェア開発における方法論について定義された The Twelve-Factor App にも CI/CD についての記載がされています。
本章ではただ CI/CD を構築するのではなくこの The Twelve-Factor App にも沿った CI/CD の設計を意識して解説しています。
#@# 時間があれば

== 一般的な CI/CD フロー
　CI/CD はプロジェクト要件によって自動化プロセスを自由に定義できることところが魅力です。
しかし、初めて CI/CD を導入しようとしている方にとっては何をすればいいかわからないかもしれません。
ここでは CI/CD 入門ということでどのようなプロジェクトでも利用できる一般的な CI/CD フローを解説します。
CI/CD では@<strong>{各フローで実行される処理}のことを@<strong>{「ジョブ」}と呼びます。


=== プルリク/マージリクエスト
　CI/CD の旅はここから始まります。
多くのプロジェクトは GitFow や GitHub Flow に従った Gitのブランチ戦略をとってるかと思います。
その場合新規機能を Feature ブランチで開発した後、共通レポジトリにプルリク/マージリクエストを送るはずです。
このプルリク/マージリクエストイベントをトリガーにジョブを順番に実行していきます。

=== コードの静的解析
　先程のプルリク/マージリクエストイベントを検知するとコードの静的解析を行います。
例えば、javascript を利用している場合は適切な EcmaScript のバージョンで記述されているかを確認するための ESLint を実行します。
他の言語でも同様です。
いわゆる Lint を実行し、コード規約に沿っているか、推奨されるプログラムの書き方を行っているか、利用していない変数はないか、
初期化されていない変数はないか、コードエラーが出ていないかなど様々なコードやプログラム言語に関するチェックを行います。

チェックを行った後は、その結果によって後の CI を続けるか続けないかを決めます。
成功した場合は次のプロセスを実行します。
失敗した場合は失敗した旨をチャットツールなどコミュニケーションツールに知らせることもできます。

=== Unit テスト
　コードの静的解析が成功すると次に Unit テストを行います。
テストコードを記述する文化がある会社やプロジェクトでは Unit テスト実行を CI 上で自動化すると良いです。
成功した場合、 Unit テストツールによってはカバレッジをログ形式で CI 上に単に表示させることができます。
また、分析しやすいように別のグラフ系の Web サービスを連携させて表示させても良いでしょう。

=== コードのマージ
　Unit テストが成功すると開発用の共通ブランチにマージすることができます。
一般的にはマージ前に開発リーダや、上級エンジニアの方のコードレビューを行い、承認が通ったコードだけマージさせることが多いでしょう。
CI もそのようなフローに合わせて自動でマージさせずコードレビューのための承認フロー（マージブロック）を設定します。
マージブロックはレポジトリサービス標準で備わっている機能です。
マージリクエストに対してレビュアーをアサインさせレビュアーの承認がないとマージできないように設定することができます。


　また、マージされるソースコードは、CI によってコードの規約チェックや Unit テストを行うジョブをくぐり抜けてきています。
したがって、コードレビュー者は@<strong>{「ソースコード上のビジネスロジックの確認に専念」}できます。
@<strong>{「インデントが揃ってない」}や@<strong>{「使われていない変数がある」}など、コードレビュー時の@<strong>{本質外のマージリクエストの突き返し}がなくなります。
このように CI は@<strong>{「開発者」}あるいは@<strong>{「コードレビュー者」}を@<strong>{楽にする}ための@<strong>{自動化プロセス}だと言えます。
最後に、コードレビューを行った後は「マージ」ボタンを押して開発用の共通ブランチにマージします。

ここまでが CI が取り扱うジョブの流れになります。

=== ビルド
ビルドは CD が扱うプロセスになります。プログラミング言語によっては本番環境へデプロイする前にビルドのプロセスが必要になります。
例えば、モダンな javascript 開発であれば ECMAScript7 をどんなブラウザでも動作を保証するために ECMAScript5 でトランスパイルしたり、
PHP であれば composer install でフレームワークや依存モジュールをパッケージから展開する処理をここで行います。
また、時には API のドキュメントをコメントアウトのコードから生成するようなこともあるでしょう。

要するに、ここではレポジトリのソースコードを本番環境にデプロイする準備を行っています。
プロジェクトごとにビルドのコマンドが違うので、ビルドフローを洗い出し手作業を排除し、自動化のためにコマンドをこのビルドプロセスで実行しましょう。

=== デプロイ
　デプロイでは実行する環境へ合わせてビルドしたコード群を各環境へ配置して、システムを動かせる状態にします。
ここで言う「実行する環境」とは本番環境だけでなく、「ステージ環境」や「統合開発環境」などのことも指します@<fn>{staging}。
つまり、@<strong>{「目的の環境へコードをデプロイし正常にシステムが動く環境を提供するプロセス」}をここに記述します。
AWS を例にすると、
ステージ環境では、費用削減のためにオートスケーリングの台数を 1 台かつダウンタイム発生しても問題ないので単にインスタンスを入れ替えるデプロイ方法を定義する。
本番環境では、オートスケーリング 5 台でダウンタイムを発生させたくないのでローリングアップデート方式でデプロイする。
といった感じで環境に合わせたデプロイプロセスをここで定義します。


このデプロイプロセスで重要なことは、目的の環境へデプロイする際は本番もステージも同じ一つ前のビルドプロセスで作成されたコード群を使ってデプロイしなければならないことです。
すなわち、ビルド 1 コード群に対して複数のデプロイ先を定義できるようにプロセスを作る必要があります。
なぜ同じビルドされたコード群を使わなければならないかというと、ステージと本番のコード群の同一性を担保するためです。
ステージと本番で違うビルドプロセスで作成されたコード群をステージへデプロイし、システムテストをしてもそれはステージ用にビルドされたコード群をテストしたのであって本番用のビルドされたコード群と全く同一であるという保証は厳密にはできません。
このビルドによる環境の差を防ぐために同一ビルドプロセスでビルドを行う必要があります。


複数のデプロイ先を定義するために重要なものが@<strong>{「環境変数」}です。
デプロイの自動化プロセスをうまく回すためにはこの環境変数が重要になります。
ビルドプロセスでは環境に依存したコードを含めずにビルドを行い、デプロイプロセス時に環境変数によってデプロイ先を分離することができます。

//footnote[staging][プロダクトや企業の伝統、開発体制によって呼び方が変わるので言葉の定義はあえてしません。]

== 無料で使える CI サービス
=== GitLabRunner
 GitLabRunner は コードレポジトリサービスを提供している GitLab の CI サービスです。
GitLabRunner は GitLab 公式がメンテナンスしている CI を実行するサーバ「Shared Runner」を提供しています。 
OSS 開発者の場合は無料で「Shared Runner」を利用できます。
また、プライベートレポジトリの場合はグループ毎に 月 2000 時間まで利用できます。

オンプレミスで GitLab を運用しているプロジェクトのために GitLabRunner が実行できるパッケージを各 Linux ディストリビューションで提供しています。
社内のセキュリティポリシーでパブリックなサーバにソースコードをおいてはいけない場合はこの GitLabRunner のパッケージをサーバにインストールしてオンプレミスで CI を実行することもできます。


==== gitlab-ci.yml で CI プロセスを記述する
 「Shared Runner」を利用する場合 プロジェクトフォルダに「gitlab-ci.yml」を追加することですぐに CI のプロセスが実行できるようになります。
「gitlab-ci.yml」は CI プロセスを定義する yml ファイルです。
GitLabRunner はレポジトリに置かれている gitlab-ci.yml のファイルの中を解析し、ファイルに定義されている命令通りにプロセスを実行します。



=== CircleCI
　「GitLabRunner」とは違いどんなレポジトリサービスでも CI を実施できるのが CircleCI です。
#@# Circle CI について


他にも TravisCI や Jenkins など様々な CI サービスがありますので、プロジェクトにあった CI ツールを選択して見てください。

== AWSが提供する CI/CD サービス
AWS にも CI/CD サービスが提供されています。

=== AWS CodeBuild
　AWS CodeBuild は クラウド上で実行できるビルド環境を完全マネージドでカスタマイズできるビルドサービスです。
ビルド用のサーバやソフトウェアの設定、実行環境はすべて AWS が管理しユーザはサーバを気にせずビルドスクリプトだけに集中できます。
また、Docker ベースで実行環境を作成できるため、CodeBuild が用意していない実行環境を利用したい場合は自分の Docker イメージ上でビルド環境をカスタマイズすることもできます。
Code Build がデフォルトで提供している実行環境は下記のとおりです。

・android 28	
・Docker 18
・dotnet 2.2	
・Golang 1.12	
・NodeJS 8、10	
・java openjdk8、openjdk11
・php 7.3	
・python 3.7	
・ruby 2.6

Docker がデフォルトで提供されているので提供されていないランタイムは Docker on Docker を利用して自分で用意した Docker イメージでビルド内容をカスタマイズしましょう。

=== AWS CodeDeploy
 AWS CodeDeploy は AWS のコンピューティングサービス（Amazon EC2、AWS Fargate、AWS Lambda）へのデプロイを自動化できる完全マネージドサービスです。
デプロイ対象ファイルの取得元として S3 または GitHub が選択できます。
またデプロイ先が EC2 の場合 は Tag や AutoScaling グループを選択できるので、複数サーバにデプロイすることも可能です。
更に、複数サーバの場合はどのようにデプロイを実行するかも指定できます。

既存のプロジェクトで CI を GitLab Runner や CircleCI などを利用している場合 AWS 環境へデプロイする際にこの CodeDeploy を組み合わせて使う場合がよくあります。


=== AWS CodePipeline
 AWS CodePipeline は一連の CI/CD のワークフローを定義し、デプロイメントパイプライン（パイプライン）を完全マネジメントで作成できるサービスです。
デプロイメントパイプラインとはソースコードからビルド、テスト、デプロイなど CI/CD の各ジョブを自動化したプロセスのことです。
多くのプロジェクトではこのパイプラインが異なると思いますが AWS CodePipeline を利用することでプロジェクトごとのパイプラインを一元管理し、
他のプロジェクトでも再配布可能な形で管理することができます。
これによっていわゆるデプロイ職人と呼ばれる、デプロイの属人化を防ぐとともにデプロイの標準化とパイプラインのバックアップを AWS 上で行うことができます。


#@# ===[column] CI/CD ツールの乱立とクラウドベンダーの台頭
#@# 　AWS などのクラウドベンダーが台頭してくる前までは CircleCI や Jenkins、TravisCI など CI/CD 専門のツールがプロジェクトに導入されることが多かったと思います。
#@# しかし最近はクラウドベンダーが独自の CI/CD ツールを発表しています。
#@# またレポジトリ管理サービスである GitLab は独自の GitLabRunner を提供しています。
#@# さらに、GitHub は最近 GitHub 独自の CI/CD サービスとして GitHub Actions 一般公開することを発表しました。
#@# 　CI/CD の需要が高まったため様々なベンダーが独自の CI/CD サービスをリリースして CI/CD ツールが乱立している状況にあります。
#@# このような状況下でユーザはプロジェクトにあった適切な CI/CD ツールを取捨選択しなければいけない時代になっています。
#@# またよりプロジェクトの状況にあった CI/CD にアップデートしていく必要もあります。
#@# どの CI/CD が優れているかはここでは述べませんが、一度普段利用している CI/CD ツール以外を調査してい見て
#@# 見直してみてもいいのではないかと思います。

#@# ===[/column]


== 開発を楽にする CI 環境の作り方
　この項では、実際の本番構成を想定した、CI 環境の例を説明します。

=== GitLabRunnerをつかった CI 環境の例



== 特徴を知って使い分けるデプロイパターン
　最近のプロジェクトでは、デプロイ時に無停止を要求されるプロジェクトも多くあります。
デプロイ時の障害やアップデートの影響を最小限に抑えるためのデプロイパターンと呼ばれるデプロイの方法がいくつかあるので紹介します。

=== ローリングアップデート
　ローリングアップデートとは、本番インスタンスを最新バージョンのインスタンスと徐々に入れ替えていくアップデートの方法です。
次の図のようにアップデートができます。
#@# ローリングアップデートの図
最終的には全てのインスタンスが最新バージョンに入れ替わりますが、途中古いバージョンと新しいバージョンが混在することになりますので
アップデート内容は新・旧両方動作するようなアップデート内容でないとこの方法でアップデートできないことに注意しましょう。

=== ブルー・グリーンデプロイ
　ブルー・グリーンデプロイとは、最新バージョンがデプロイされている環境を本番と完全に同様の構成で作成し
DNSのレコードやロードバランサーのルーティングを古い環境から新しい環境へと切り替えることでアップデートを行う方法です。
#@# ブルー・グリーンデプロイの図

このアップデートは、DNSのレコード切り替えによって簡単に古いバージョンと新しいバージョンが切り替えられるので問題があった場合はすぐに古いバージョンへと切り戻しが行なえます。
しかし、完全に新しいバージョンへ切り替えてしまうので、事前の動作チェックをしっかりと行う必要があります。
ローリングアップデートとは異なり、新しいバージョンで問題があった場合は最悪切り戻すまでサービスが停止してしまいますので考慮する必要があります。

== 本番環境にEC2インスタンスを利用するデプロイパターン
#@# === レポジトリにGitLabを利用する場合
#@# ==== AutoScaling 環境下でのローリングアップデート例

=== レポジトリにGitHubを利用する場合
==== AutoScaling 環境下でのローリングアップデート例
==== AutoScaling 環境下でのブルー・グリーンデプロイ例

== 本番環境にサーバレスを利用するデプロイパターン
=== S3バケットにデプロイ後CloudFrontのキャッシュを自動削除する例

== 目指せ最速デプロイ ElasticBeansTalk を使ったデプロイパターン

== 付録
#@# gitlab-ci.yml 
#@# GitLabRunner をコマンド一発で作成できる CloudFormation
#@# CodeBuild サンプル yml