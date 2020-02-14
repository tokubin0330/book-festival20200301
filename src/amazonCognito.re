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

==[nonum] 機能
Amazon Cognito(以下、Cognito)では、ユーザープールを作成する事によって、ユーザーがアプリケーションに登録・ログインできるようになります。
FacebookやTwitterやGoogleGoogleアカウントを利用したログインもサポートすると共に、多段階認証の機能もサポートしています。

Cognito には、ユーザーのサインアップとサインインのためのカスタマイズ可能な組み込みUIが用意されています。このUIの文言はデフォルトでは英語で設定されていますが
カスタマイズによって日本語に変更する事もできます。

Cognitoの詳細な設定はコンソール画面から行なう事ができます。パスワードの文字数制限もこちらで設定する事ができます。

==[nonum] どんな時に使うの？
Cognitoはアプリのサインアップとサインインのウェブページを設計する時に使われます。または、データのアクセス制御を行いた場合にも使われる事があります。

==[nonum] Cognito IdentityとCognito Syncについて

CognitoにはCognito IdentityとCognito Syncという2つの機能があります。

Cognito Sync は、AWS のサービスを利用するユーザーに 固有のデータストレージ を提供するサービスです。
Cognito Syncについてですが、現在はapp syncが推奨されるようになりました。

Cognito Identity により一意になったユーザー一人一人に対して、ユーザーデータを保存する場所を提供してくれます。
格納されたデータは、ローカルだけではなく、クラウドと同期して保存されます。
