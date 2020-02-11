= Amazon Simple Notification Service

//embed[latex]{
\begin{tcolorbox}[title=どんなサービス？,sharp corners]
SNSはAmazon Simple Notification は、個別または複数のメッセージを多数の受信者に送信できるマネージドプッシュ通知サービスです。
サーバのアラート通知からアプリのトランザクション通知などをメールやチャット、SMS など様々なシチュエーションと形式でプッシュ通知を送信することができます。
\end{tcolorbox}
//}


//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}


==[nonum] 概要

Amazon SNS は様々なシチュエーションに対応したプッシュ通知サービスをマネージドで提供します。
プッシュ通知を送る形式はサービスによって沢山の選択肢があります。
Amazon SNS では複数の形式（Email、SMS、モバイルプッシュ）を使用するエンドユーザに対して一括送信ができます。



==[nonum] SNS が送信するプッシュ通知の形式
SNS が送信できるプッシュ通知の形式をご紹介します。

・Webhook  
　HTTP、HTTPS  
・メール送信  
　Email、Email-JSON  
・メッセージ送信  
　SMS   
・AWS サービス  
　Amazon SQS、AWS Lambda  
・モバイル通知  
　Amazon SNS モバイル通知  

Webhook が利用できるので様々なサードパーティ製のツールと連携できます。
例えば Slack などのチャットツールや GitHub API などと連携することで自動でチャットを送ったり
GitHub の Issue を作成するなどの連携ができます。

==[nonum] SNS が受信するイベントソース
SNS は 他の AWS サービスからのイベントを SNS へ集約することができます。
これによってイベント駆動型の自動ワークフローを実行することができます。
ここでは SNS と連携できる送信元となるサービスをご紹介します。

コンピューティング: Amazon EC2 Auto Scaling、AWS Lambda、ELB 等

ストレージ: Amazon EFS、Amazon Glacier、Amazon S3 等

データベース: Amazon DynamoDB、Amazon ElastiCache、Amazon Redshift、Amazon RDS 等

ネットワーク: Amazon Route 53、Amazon VPC 等

開発者ツール: AWS Code シリーズ

管理ツール: Amazon CloudWatch Alarms、Amazon CloudWatch Events、AWS CloudFormation 等

顧客エンゲージメント: Amazon Pinpoint、Amazon SES 等


====[nonum] 料金
ビルドにかかった時間とビルド用サーバのスペックで料金が変わります。

■ 無料枠

