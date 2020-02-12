= AWS Certificate Manager

//embed[latex]{
\begin{tcolorbox}[colframe=black,colback=white,colbacktitle=black,coltitle=white,coltext=black,title=どんなサービス？,sharp corners]
AWS Certificate ManagerはAWSが提供している無料SSL証明書サービスになります。
AWS Certificate ManagerはAWSベースのウェブサイトとアプリケーション用のパブリックSSL/TLS証明書の複雑な作成と管理を処理します。
\end{tcolorbox}
//}

//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}

==[nonum] どんなサービス？
AWS Certificate ManagerはAWSが発行したSSL証明書の事です。AWS Certificate Managerを使用して、Elastic Load Balancing、Amazon CloudFront、Amazon API Gateway、AWS Elastic Beanstalk等で使用する証明書をプロビジョニングする事ができます。

==[nonum] AWS Certificate Managerのメリット
AWS Certificate Managerでは、Elastic Load BalancingやAPI GatewayなどのACM統合サービスで使用する、パブリックやプライベートの SSL/TLS 証明書のプロビジョニングについて、追加料金はかかりません。
お支払いいただくのは、アプリケーションを実行するために作成したAWSリソースの料金です。

==[nonum] ワイルドカードについて
AWS Certificate Managerでは、ドメイン名にアスタリスク (*) を使うことで、同じドメイン内の複数のサイトを保護できるワイルドカード名を含むAWS Certificate Manager証明書を作成することができます。
たとえば、*.example.com は、www.example.com と images.example.com を保護する事ができます。
ただし*.example.comで証明書を発行した場合、example.comといったドメインは保護されません。

==[nonum] アルゴリズム
証明書では、アルゴリズムやキーサイズを指定する必要があります。現在、次のパブリックキーアルゴリズムがAWS Certificate Managerでサポートされています。

・2048 ビット RSA (RSA_2048)

・4096 ビット RSA (RSA_4096)

・Elliptic Prime Curve 256 ビット (EC_prime256v1)

・Elliptic Prime Curve 384 ビット (EC_secp384r1)