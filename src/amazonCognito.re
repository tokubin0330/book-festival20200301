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



==[nonum] どんな時に使うの？
Cognitoはアプリのサインアップとサインインのウェブページを設計する時に使われます。

