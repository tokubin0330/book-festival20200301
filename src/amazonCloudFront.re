= Amazon CloudFront

//embed[latex]{
\begin{tcolorbox}[colframe=black,colback=white,colbacktitle=black,coltitle=white,coltext=black,title=どんなサービス？,sharp corners]
Amazon CloudFrontとは、ユーザーへの静的および動的ウェブコンテンツ (.html、.css、.js、イメージファイルなど) の配信を高速化するウェブサービスです。
CloudFront ではエッジロケーションと呼ばれるデータセンターの世界規模のネットワークを通じてコンテンツが配信されます。
\end{tcolorbox}
//}

//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}

==[nonum] 概要
Amazon CloudFrontは、データ、動画、アプリケーション、および API をすべて開発者にとって使いやすい環境で、低レイテンシーの高速転送により世界中の視聴者に安全に配信する高速コンテンツ配信ネットワーク (CDN) サービスです。

==[nonum] どんな時に使うの?

・Amazon CloudFrontを使用することで、AWSバックボーンネットワークおよびAmazon CloudFrontエッジサーバーの利点を活用して、ウェブサイトを閲覧するビューワーに高速で、安全で、信頼性の高いエクスペリエンスを提供できます。

・Amazon S3 バケットを使用すると、静的コンテンツを簡単に格納し、配信することができます。

==[nonum] Amazon CloudFrontの機能
Amazon CloudFrontには以下のような機能があります。

====[nonum] コンテンツのキャッシュ
初回アクセス時に、サーバーから取得したコンテンツをキャッシュします。
次回のアクセス以降は、キャッシュの有効期限が切れるまでキャッシュされたコンテンツを返すことにより表示を高速化する事ができます。

====[nonum] SSLによる通信の暗号化
Amazon CloudFrontでは、SSL証明書を利用したSSL暗号化通信が可能です。ユーザーが用意した独自のSSL証明書を導入することができます。

====[nonum] サイトの高速化
サイトの表示が遅い、大容量ファイルのダウンロードが遅いといった場合に、CloudFrontを利用することで配信を高速化することができます。 
海外からのユーザが多い場合などでサイトの表示速度が気にになる場合などにも効果を発揮しますが、日本国内のみの配信という場合でも高速化の効果を得られます。

====[nonum] 署名付きURL
一定時間だけアクセスを許可するためのURLを発行し、URLを通知た限定的なユーザーにのみ公開することができる機能です。

====[nonum] カスタムエラーページ
オリジンからエラーコードが返された場合、あらかじめ設定したエラーページを表示することができます。

====[nonum] 地域制限
Amazon CloudFrontへ接続するユーザーの地域情報に基づいて、アクセスを許可または拒否することが可能です。

====[nonum] ストリーミング配信
Amazon CloudFrontでは、Webサービスのコンテンツ配信に加えて、映像や音声のストリーミング配信にも対応しています。

====[nonum] アクセス分析機能
ユーザーがどの国からアクセスしてきているかをCloudFrontで検出することができます。

====[nonum] CDN経由のデータ送信
Amazon CloudFrontでは、CDNから配信されたコンテンツからのPOSTやPUT、DELETEなどの処理をサポートしています。

====[nonum] セキュリティ機能
Amazon CloudFrontは、ネットワークレベルとアプリケーションレベルの両方で保護される非常に安全性の高いCDNです。
トラフィックとアプリケーションは、AWS Shield標準のようなさまざまな組み込み保護機能を追加費用なしで利用できます。
また、AWS Certificate Manager（ACM）といった設定可能な機能を使用して、追加コストなしでカスタムSSL証明書を作成、管理することもできます。

==[nonum] Amazon CloudFrontとAmazon Route 53
AWS の正式な DNS サービスである Amazon Route 53 を使用すると、「エイリアス」レコードを構成できます。
このレコードによって、DNS 名の apex またはルート（example.com）を Amazon CloudFront ディストリビューションにマッピングできます。
Amazon Route 53 は、CloudFront ディストリビューション用に正しい IP アドレスが設定されたエイリアスレコードの各リクエストに応答します。
Route 53 では、CloudFront ディストリビューションにマッピングされているエイリアスレコードへのクエリは課金されません。
このようなクエリは、Amazon Route 53 の使用状況レポートに「Intra-AWS-DNS-Queries」として記載されます。

//embed[latex]{
\clearpage
//}

==[nonum] Amazon CloudFrontのコストは?
Amazon CloudFront の料金は、データ転送（アウト）、HTTP/HTTPS リクエスト、無効リクエスト、および CloudFront ディストリビューションに関連付けられた専用 IP 独自 SSL 証明書という 4 つの領域での実際のサービス使用状況に基づいて請求されます。
AWS 無料利用枠を使うと、Amazon CloudFront を無料で開始していただけます。サインアップしていただくと、AWS の新規お客様は、Amazon CloudFront において 50GB のデータ送信（アウト）と 2,000,000 件の HTTP および HTTPS リクエストを毎月 1 年間ご利用いただけます。
