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


==[nonum] どんなサービス？
Amazon API Gateway は、あらゆる規模の REST および WebSocket API を作成、公開、保守、モニタリング、および保護するためのAWSサービスです。
API開発者は、AWSまたは他のウェブサービス、AWSクラウドに保存されているデータにアクセスするAPIを作成できます。

==[nonum] どんな時に使うの？

Amazon API Gatewayは、以下のようなREST APIを作成する事ができます。

・HTTP ベース

・ステートレスなクライアントサーバー通信を可能にする RESTプロトコルに準拠しています。

・GET、POST、PUT、PATCH、DELETE などの標準のHTTPメソッドを実装しています。

==[nonum] Amazon API Gatewayのコストは？

Amazon API Gatewayにはデータ転送量による課金がされます。10TBまで1GBあたり$0.09が課金されます。
10TBを越えると、容量に応じた割引があります。キャッシングを有効にしている場合、容量と時間に応じた料金が課金されます。キャッシング容量が0.5GBの場合、1時間あたり$0.02になります。

==[nonum] Amazon API GatewayとLambdaの統合

Amazon API Gatewayは、Amazon Lambdaと合わせて利用することで、より便利に活用する事ができます。


==[nonum] Amazon API GatewayのCORS設定機能

Amazon API Gatewayを利用してAPIを構築している場合、Amazon API GatewayのCORS設定機能が便利です。
CORSは簡単に言うと、 ウェブサイトが異なるドメインに対するAPIリクエストをブロックする仕組みです。
しかし、Amazon API GatewayのバックエンドにLambdaを利用しており、かつ Lambda Proxyで利用している場合、API GatewayのCORS設定は利用できません。

