= AWS CI/CD入門
　皆さん、CI/CDしてますか？

== CI/CDとは
　CI/CD という言葉は今や IT 業界では一般的になっており、CI/CDが何を示しているのかを説明する機会が減ってきています。
またプロジェクト毎や会社毎または、個人の認識の違いで CI/CD が取りうる範囲が少し違うこともしばしばあります。
ここではなるべくそういった言葉の齟齬をなるべくなくすために CI/CD が取り扱う範囲を定義します。

 CI/CD は英語では「Continuous Integration/Continuous Delevary」日本語に訳すと「継続的インテグレーション/継続的デリバリー」といいます。
　ここで 「CD にデプロイは入らないの？」と疑問に思った方のために RedHat #@# 脚注参照 
が定義する CI/CD を例にここでしっかりと言葉の定義をしていきます。

#@# 脚注
https://www.redhat.com/ja/topics/devops/what-is-ci-cd#

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

=== デリバリー

=== デプロイ


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


他にも TravisCI や Jenkins など様々な CI サービスがありますので、プロジェクトにあった CI ツールを選択して見てください。

== AWSが提供する CI/CD サービス
AWS にも CI/CD サービスが提供されています。

=== AWS CodeBuild
=== AWS CodeDeploy
=== AWS CodePipline
=== AWS CodeStar

===[column] CI/CD ツールの乱立とクラウドベンダーの台頭

aa

===[/column]


== 開発を楽にする CI 環境の作り方
=== GitLabRunnerをつかった CI 環境の例

== 特徴を知って使い分けるデプロイパターン
=== ローリングアップデート

#@# ローリングアップデートの図
=== ブルー・グリーンデプロイ

#@# ブルー・グリーンデプロイの図
=== カナリアデプロイ

#@# カナリアデプロイの図
　　　

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