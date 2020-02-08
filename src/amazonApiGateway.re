= Amazon API Gateway

//embed[latex]{
\begin{tcolorbox}[colframe=black,colback=white,colbacktitle=black,coltitle=white,coltext=black,title=どんなサービス？,sharp corners]
Amazon API Gateway は、数回クリックするだけで、簡単に API の作成、配布、保守、 監視、保護が行えるフルマネージドなサービスです。
どのようなスケールにも対応するパフォーマンスを低コストでご利用いただけます。
\end{tcolorbox}
//}

//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}


==[nonum] 概要
Amazon API Gateway は、あらゆる規模の REST および WebSocket API を作成、公開、保守、モニタリング、および保護するためのAWSサービスです。
API開発者は、AWSまたは他のウェブサービス、AWSクラウドに保存されているデータにアクセスするAPIを作成できます。

==[nonum] Amazon API Gatewayのユースケース（REST API）

Amazon API Gatewayは、以下のようなREST APIを作成する事ができます。

・HTTP ベース

・ステートレスなクライアントサーバー通信を可能にする RESTプロトコルに準拠しています。

・GET、POST、PUT、PATCH、DELETE などの標準のHTTPメソッドを実装しています。

==[nonum] Amazon API Gatewayのユースケース（WebSocket API）

Amazon API Gateway は、次のような WebSocket API 管理機能を提供します。

・接続とメッセージのモニタリングとスロットリング

・AWS X-Ray を使用した、API からバックエンドサービスへのメッセージのトレース。

・HTTP/HTTPS エンドポイントとの簡単な統合

==[nonum] Amazon API Gatewayのコストは？

Amazon API Gatewayにはデータ転送量による課金がされます。10TBまで1GBあたり$0.09が課金されます。
10TBを越えると、容量に応じた割引があります。キャッシングを有効にしている場合、容量と時間に応じた料金が課金されます。キャッシング容量が0.5GBの場合、1時間あたり$0.02になります。

==[nonum] Amazon API GatewayとLambdaの統合

Amazon API Gatewayは、Amazon Lambdaと合わせて利用することで、より便利に活用する事ができます。

====[nonum] ステップ 1: LambdaコンソールでAmazon Lambda関数を作成します

このステップでは、Lambdaコンソールを使用して簡単なLambda 関数を作成します。次の手順でこの関数を使用します。

//embed[latex]{
\clearpage
//}

====[nonum] ステップ 2: API Gateway コンソールで REST API を作成する 

このステップでは、API Gateway コンソールで簡単な REST API を作成し、バックエンドとしてAmazon Lambda関数をこれにアタッチします。

====[nonum] ステップ 3: API Gatewayコンソールに REST API をデプロイする

ステップ 2 を完了すると API が作成されますが、まだ実際に使用することはできません。これをデプロイする必要があるためです。

====[nonum] ステップ 4: Lambdaコンソールで 2 番目のLambda関数を作成します。

このステップでは、2 番目のバックエンドの Lambda 関数を作成します。これは、入力パラメータを 1 つ受け取ります。ステップ 5では、独自の GET メソッドがある API に子レスポンスを作成します。パラメータ値をこの新しい関数に渡すようにメソッドを設定します。

====[nonum]　ステップ 5: API Gateway コンソールでリソース、メソッド、パラメータを REST API に追加します。

リソースとメソッドは、REST API の名詞および動詞です。このステップでは、API に子リソースを作成し、GET メソッドをこのリソースに追加します。
クエリ文字列パラメータを新しいメソッドに追加して、ステップ 4 で作成した Lambda 関数の入力パラメータと一致させます。
新しい関数にこのメソッドを統合して、ユーザー入力を取得し、Lambda 関数の入力 (同じくシンプルな文字列) にこれをマッピングします。

==[nonum] Amazon API GatewayのCORS設定機能

Amazon API Gatewayを利用してAPIを構築している場合、Amazon API GatewayのCORS設定機能が便利です。
CORSは簡単に言うと、 ウェブサイトが異なるドメインに対するAPIリクエストをブロックする仕組みです。
しかし、Amazon API GatewayのバックエンドにLambdaを利用しており、かつ Lambda Proxyで利用している場合、API GatewayのCORS設定は利用できません。

//embed[latex]{
\clearpage
//}

//embed[latex]{
\begin{tcolorbox}[title=コラム：似たようなサービス,sharp corners]
aaa
\end{tcolorbox}
//}