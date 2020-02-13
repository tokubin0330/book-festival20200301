= AWS Lambda
キーワード：/サーバレス/自動化/コード実行
//embed[latex]{
\begin{tcolorbox}[title=どんなサービス？,sharp corners]
AWS Lambda（以下 Lambda）は、サーバ管理が不要なコードを実行するサービスです。
ユーザは Lambda にプログラムソースコードをアップロードするだけで、他の AWS サービスや
ウェブ、モバイルアプリからコードを実行することができます。
\end{tcolorbox}
//}

//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}


==[nonum] Lambda の特徴
===[nonum] サーバ管理が不要
コードを実行するためのサーバや、ミドルウェアの設定は不要です。
ユーザはコードを実行する言語を選ぶだけで好きなコードを実行することができます。
現在 Lambda がサポートしている言語は Java、Go、PowerShell、Node.js、C#、Python、Ruby です。

===[nonum] スケーリングの自動化
Lambda 自体の冗長化やスケーリングも自動で行ってくれます。
Lambdaは、同時に呼び出された Lambda を実行数分自動でスケーリングします。
したがって、サーバのチューニングやスペックに関して気にすることなくコードを実行することができます。

===[nonum] 他の AWS サービスとの連携
Lambda の一番の特徴は、他の AWS サービスと連携できるところです。
例えば、Lambda 上で永続的に保存したいデータは S3 や DynamoDB へ保存させるコードを実装することで、
サーバレスアプリケーションを実現できます。
また、 API GateWay と組み合わせることでサーバレスな REST API を作成することもできます。
さらに、特定の AWS サービスとはネイティブに Lambda と連携できるため、直接 Lambda を実行できます。
下記がLambda とネイティブに連携できる AWS サービスです。

コンピューティング：ALB

ストレージ：S3 

データベース：DynamoDB

ストリーミング：Kinesis、

顧客エンゲージメント：SES

アプリケーション統合：SQS、SNS、Step Functions

運用：CloudWatch、CloudFormation、CodeCommit、CodePipeline

コンテンツ配信：CloudFront、API GateWay

など

==[nonum] ユースケース
Lambda を応用させると様々なバックエンドで実現していた処理をサーバレスで実現できるようになります。
ここではその一例をご紹介します。

・S3に画像ファイルをアップロード後、リサイズしたサムネイル画像を生成

・CloudWatch ログなどのストリーミングデータをフィルタリング & 分析

・モバイルバックエンドとして API GateWay と Lambda による API リクエストの認証・処理
