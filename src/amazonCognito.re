= Amazon Cognito

//embed[latex]{
\begin{tcolorbox}[colframe=black,colback=white,colbacktitle=black,coltitle=white,coltext=black,title=どんなサービス？,sharp corners]
Amazon Cognitoは、ウェブアプリケーションやモバイルアプリケーションの認証をしてくれるサービスです。
ユーザーは、ユーザー名とパスワードを使用して直接サインインするか、Facebook、Amazon、Google、Apple などのサードパーティーを通じてサインインできます。
\end{tcolorbox}
//}

//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}

==[nonum] Amazon Cognito の機能

====[nonum]　ユーザープール

ユーザプールは Amazon Cognito のユーザディレクトリです。ユーザープールを使用することで、アプリユーザーは、Amazon Cognito からウェブやモバイルアプリにサインインするか、サードパーティーの ID プロバイダー (IdP) を通じて連携することができます。

ユーザーが直接またはサードパーティを通じてサインインするかどうかにかかわらず、ユーザープールのすべてのメンバーには、SDK を通じてアクセスできるディレクトリプロファイルがあります。

====[nonum]　ID プール

ID プールを使用すると、ユーザーは一時的な AWS 認証情報を取得して、Amazon S3 や DynamoDB などの AWS サービスにアクセスできます。ID プールは、匿名ゲストユーザーと、ID プールのユーザーを認証するのに使用できる次の ID プロバイダーをサポートします。

・Amazon Cognito ユーザープール

・Facebook、Google でのソーシャルサインイン、Login with Amazon

・OpenID Connect (OIDC) プロバイダ

・SAML ID プロバイダー

・開発者が認証した ID

ユーザープロファイル情報を保存するには、ID プールをユーザープールに統合する必要があります。
