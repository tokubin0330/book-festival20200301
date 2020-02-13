= Amazon Route53

//embed[latex]{
\begin{tcolorbox}[colframe=black,colback=white,colbacktitle=black,coltitle=white,coltext=black,title=どんなサービス？,sharp corners]
Amazon Route53は、可用性と拡張性に優れたクラウドのドメインネームシステム (DNS) ウェブサービスです。
Amazon Route53ではドメイン名登録も提供します。example.comのようなドメイン名を購入および管理でき、Amazon Route53でお客様のドメインのDNS設定が自動的に構成されます。
\end{tcolorbox}
//}

//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}

==[nonum] どんな時に使うの？
Amazon Route53 は、AWSの他の機能やサービスと連動するように設計されています。
Amazon Route53 を使用して、Amazon EC2 インスタンス、Amazon S3 バケット、Amazon CloudFront ディストリビューションおよびその他の AWS リソースとドメイン名をマッピングできます。
AWS Identity and Access Management (IAM) サービスと Amazon Route53 を組み合わせることで、DNS データを更新するユーザーをきめ細かく管理できます。

==[nonum] Amazon Route53のレコードタイプ
Amazon Route53がサポートするレコードタイプは以下になります。

・A（アドレスレコード）

・AAAA（IPv6 アドレスレコード）

・CNAME（正規名レコード）

・MX（メール交換レコード）

・NS（ネームサーバーレコード）

・PTR（ポインターレコード）

・SOA（管理情報の始点レコード）

・SPF（センダー ポリシー フレームワーク）

・SRV（サービス ロケーター）

・TXT（テキストレコード）

==[nonum] Amazon Route53のコストは？
Amazon Route 53はとても低コストでサービスが提供されています。Route53は前払いは一切なく、あくまで使用した分だけ支払う従量制です。最低料金もありません。

==[nonum] Amazon Route53のルーティングポリシー
Amazon Route 53はクエリに応答する方法をルーティングポリシーで設定する事ができます。代表的なルーティングポリシーを記載します。

・位置情報ルーティングポリシー

ユーザーの地理的場所に基づいて、トラフィックが処理するリソースを決定します。地理的場所は大陸や国などが指定できます。

・フェイルオーバールーティングポリシー

障害や不具合が発生した時に、正常とは違うリソースにルーティングする事ができます。

・加重ルーティング

単一のドメイン名、またはサブドメイン名に複数のリソースを関連付けて、各リソースにルーティングされる事ができます。


