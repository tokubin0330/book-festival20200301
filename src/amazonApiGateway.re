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

API Gatewayは、以下のようなREST APIを作成する事ができます。

・HTTP ベース

・ステートレスなクライアントサーバー通信を可能にする RESTプロトコルに準拠しています。

・GET、POST、PUT、PATCH、DELETE などの標準のHTTPメソッドを実装しています。

==[nonum] API Gatewayのユースケース

API Gateway は、次のような REST API 管理機能を提供します。

・OpenAPI に対する API Gateway 拡張を使用した SDK の生成と API ドキュメントの作成のサポート。

・HTTP リクエストのスロットリング