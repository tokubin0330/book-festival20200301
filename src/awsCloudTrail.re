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

==[nonum] 概要
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


==[nonum] AWS CloudTrailのユースケース
AWS CloudTrailのユースケースとして、以下のような例があります。

・管理コンソール：AWSアカウントのルートユーザーによるログイン履歴

・EC2：インスタンスの操作履歴（削除など）

・KMS：KMSで管理されている鍵の使用や削除履歴

//embed[latex]{
\clearpage
//}

==[nonum] AWS CloudTrailのコストは？
AWS CloudTrailでは、サポートされているAWSのサービスのすべての管理イベントに対する過去90日間のアカウントアクティビティを、無料で表示、フィルタリング、ダウンロードできます。

また、各リージョンの管理イベントの 1 つのコピーを配信する証跡を無料で設定できます。AWS CloudTrailの証跡が設定されると、お客様の使用量に基づいてAmazon S3の料金が適用されます。
すべてのデータイベント、またはそのリージョンで記録された管理イベントの追加コピーについては、料金が発生します。 
さらに、証跡でInsightsイベントを有効にすることで、AWS CloudTrail Insights を選択できます。
AWS CloudTrail Insights の分析では書き込み管理イベントが発生し、そのリージョンで分析されたイベントの数に基づいて請求されます。

====[nonum] 管理イベント
管理イベントは、AWSアカウントのリソースに対して実行される管理オペレーション (「コントロールプレーン」) の可視性を提供します。
例えば、Amazon CloudTrailによって、Amazon EC2インスタンスの起動や Amazon S3バケットの作成などのAPIコールの管理イベントが配信されます。
各リージョン内の管理イベントの最初のコピーは、無料で配信されます。それ以降の管理イベントのコピーは、イベント10万件あたり2.00USDが課金されます。

====[nonum] データイベント
データイベントは、リソース上またはリソース内部で実行されるリソースオペレーション (「データプレーン」) についての可視性を提供します。
データイベントは、大量のアクティビティであることが多く、Amazon S3オブジェクトレベルの APIやLambda 関数、Invoke APIなどの操作が含まれます。
データイベントは指定した Lambda 関数とAmazon S3バケットについてのみ記録され、イベント10万件あたり0.10USDが課金されます。

====[nonum] CloudTrail Insights
CloudTrail Insights イベントは、分析された 100,000 の書き込み管理イベントごとに 0.35USD が請求されます。
CloudTrail Insights が異常なアクティビティを検出すると、Insights イベントが配信されます。

//embed[latex]{
\clearpage
//}

//embed[latex]{
\begin{tcolorbox}[title=コラム：似たようなサービス,sharp corners]
aaa
\end{tcolorbox}
//}