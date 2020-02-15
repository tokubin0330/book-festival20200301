= Amazon CloudFront
キーワード：CDNサービス/キャッシュ/ストリーミング配信/高速化
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

==[nonum] どんな時に使うの?

Amazon CloudFrontを使用することで、AWSバックボーンネットワークおよびAmazon CloudFrontエッジサーバーの利点を活用して、ウェブサイトを閲覧するビューワーに高速で、安全で、信頼性の高いエクスペリエンスを提供できます。

==[nonum] Amazon CloudFrontの機能
Amazon CloudFrontには以下のような代表的な機能を幾つか記載します。

====[nonum] コンテンツのキャッシュ
初回アクセス時に、サーバーから取得したコンテンツをキャッシュします。
次回のアクセス以降は、キャッシュの有効期限が切れるまでキャッシュされたコンテンツを返すことにより表示を高速化する事ができます。

====[nonum] SSLによる通信の暗号化
Amazon CloudFrontでは、SSL証明書を利用したSSL暗号化通信が可能です。ユーザーが用意した独自のSSL証明書を導入することができます。

====[nonum] サイトの高速化
サイトの表示が遅い、大容量ファイルのダウンロードが遅いといった場合に、Amazon CloudFrontを利用することで配信を高速化することができます。 
海外からのユーザが多い場合などでサイトの表示速度が気にになる場合などにも効果を発揮しますが、日本国内のみの配信という場合でも高速化の効果を得られます。

==[nonum] ユースケース
HTMLや画像など、リクエストに影響されずに同じ結果になる静的コンテンツにAmazon CloudFrontを利用して配信する場合は、Amazon S3と組み合わせます。

動的コンテンツはEC2などのコンピューティングサービスを利用して生成されるため、Amazon CloudFrontからロードバランシングサービスであるElastic Load Balancing(ELB)を経由して、コンピューティングサービスにアクセスします。

==[nonum] Amazon CloudFrontのコストは?
Amazon CloudFrontの料金は、データ転送（アウト）、HTTP/HTTPS リクエスト、無効リクエスト、およびAmazon CloudFront ディストリビューションに関連付けられた専用 IP 独自 SSL 証明書という 4 つの領域での実際のサービス使用状況に基づいて請求されます。
AWS 無料利用枠を使うと、Amazon CloudFrontを無料で開始する事ができます。
