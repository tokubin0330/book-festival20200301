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

==[nonum] 概要
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
Amazon Route 53 では、AWS のスケールメリットを得ることができます。お客様は使用したリソースに対する料金のみを支払います。
例えば、サービスで応答したドメインごとのクエリ、サービスでドメインを管理するために使用しているホストゾーン、トラフィックポリシーやヘルスチェックなどのオプション機能に対する料金のみを支払います。
これらすべては低コストで、最低使用量の条件や前払いの義務はありません。