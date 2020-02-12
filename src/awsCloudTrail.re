= AWS CloudTrail

//embed[latex]{
\begin{tcolorbox}[title=どんなサービス？,sharp corners]
AWS CloudTrailとはAWSアカウントで利用された全ての操作（APIコール）をログとして記録するサービスです。
AWS CloudTrailは、AWSアカウントを作成した瞬間に有効になります。AWSアカウントでアクティビティが発生した場合、そのアクティビティはAWS CloudTrailイベントに記録されます。
\end{tcolorbox}
//}


//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}

==[nonum] どんなサービス
AWS CloudTrailで様々な操作ログを蓄積する事によって、AWSへの不審なアクセスや操作がなされていないか、意図せぬ設定変更が行われていないかなど、さまざまなセキュリティー監視や監査に活用する事ができます。
AWS CloudTrailコンソールで、[イベント履歴] に移動して簡単にイベントを表示できます。イベント履歴により、AWS アカウントの過去 90 日間のアクティビティを表示、検索、ダウンロードできます。
さらに、AWS CloudTrail証跡を作成する事によって、AWSリソースの変更をアーカイブ、分析、応答をする事ができます。

==[nonum] AWS CloudTrailログファイル
AWS CloudTrailCloudTrailのログファイルを使用する事によって、以下のような事が可能です。

・リージョンごとに複数の証跡を作成する事ができます。

・CloudWatch Logs に送信することでAWS CloudTrailログファイルをモニタリングする事ができます。

・アカウント間でログファイルを共有する事ができます。

・AWS CloudTrail Processing Libraryを使用して、Javaでログ処理アプリケーションを作成する事ができます。

・ログファイルを検証して、AWS CloudTrailによって配信された後に変更されていないことを確認する事ができます。

・AWS CloudTrailで取得されたログファィルはデフォルトでAmazon S3に保存される。CloudWatch Logsへの連携も可能である。


==[nonum] どんな時に使うの？
AWS CloudTrailのユースケースとして、以下のような例があります。

・管理コンソール：AWSアカウントのルートユーザーによるログイン履歴

・EC2：インスタンスの操作履歴（削除など）

・KMS：KMSで管理されている鍵の使用や削除履歴

==[nonum] AWS CloudTrailのコストは？
AWS CloudTrailでは、サポートされているAWSのサービスのすべての管理イベントに対する過去90日間のアカウントアクティビティを、無料で表示、フィルタリング、ダウンロードできます。
また、各リージョンの管理イベントの 1 つのコピーを配信する証跡を無料で設定できます。AWS CloudTrailの証跡が設定されると、お客様の使用量に基づいてAmazon S3の料金が適用されます。

