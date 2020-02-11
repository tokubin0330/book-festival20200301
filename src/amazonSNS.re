= Amazon Simple Notification Service

//embed[latex]{
\begin{tcolorbox}[title=どんなサービス？,sharp corners]
Amazon Simple Notification Service（以下 Amazon SNS）は、個別または複数のメッセージを多数の受信者に送信できるマネージドプッシュ通知サービスです。
アラート通知からアプリのトランザクション通知などをメールやチャット、SMS など様々なシチュエーションと形式で通知を送信することができます。
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


==[nonum] Amazon SNS が送信するプッシュ通知の形式
Amazon SNS が送信できるプッシュ通知の形式をご紹介します。

Webhook：　　　 HTTP、HTTPS

メール送信：　　　Email、Email-JSON  

メッセージ送信：　SMS

AWS サービス：　 Amazon SQS、AWS Lambda  

モバイル通知：　　 Amazon SNS モバイル通知  

Webhook が利用できるので様々なサードパーティ製のツールと連携できます。
例えば Slack などのチャットツールや GitHub API などと連携することで自動でチャットを送ったり
GitHub の Issue を作成するなどの連携ができます。

==[nonum] Amazon SNS が受信するイベントソース
Amazon SNS は 他の AWS サービスからのイベントを Amazon  SNS へ集約することができます。
これによってイベント駆動型の自動ワークフローを実行することができます。
ここでは Amazon SNS と連携できる送信元となるサービスをご紹介します。

コンピューティング: Amazon EC2 Auto Scaling、AWS Lambda、ELB 等

ストレージ: 　　　　Amazon EFS、Amazon Glacier、Amazon S3 等

データベース: 　　　Amazon DynamoDB、Amazon Redshift、Amazon RDS 等

ネットワーク: 　　　Amazon Route 53、Amazon VPC 等

開発者ツール: 　　　AWS Code シリーズ

管理ツール: 　　　　Amazon CloudWatch、AWS CloudFormation 等

顧客エンゲージメント: Amazon Pinpoint、Amazon SES 等

==[nonum] メリット
様々な形式のプッシュ通知を Amazon SNS で完結させられるので通知先の一元管理を行うことが大きなメリットです。
また、大きな特徴として Lambda と連携ができるので自動化のワークフローを実現できます。

例えば、他の AWS サービスのイベント（アラートやS3のオブジェクト変更、AutoScalingイベント、ブラックリストからのアクセスなど）
を Amazon SNS で受信しそれをトリガーに Lambda を実行することで更に別のワークフローを実行できます。

