= AWS CDK

//embed[latex]{
\begin{tcolorbox}[colframe=black,colback=white,colbacktitle=black,coltitle=white,coltext=black,title=どんなサービス？,sharp corners]
AWS クラウド開発キット (AWS CDK) は、最新のプログラミング言語を使用してクラウドインフラストラクチャをコードとして定義し、それを AWS CloudFormation を通じてデプロイするためのオープンソースのソフトウェア開発フレームワークです。
\end{tcolorbox}
//}

//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}

==[nonum] どんな時に使うの？
CloudFormation テンプレートを生成するために実行される AWS CDK プロジェクトを、AWS CDK フレームワークを使用して作成します。
AWS CDK プロジェクトは、AWS CDK コマンドラインを使用して、または継続的デリバリーシステムで実行できます。

従来のCloudFormationでは、基本JSONやYAMLといった構造化ファイルでリソースを定義していますが、AWS CDKではアプリケーションコード（TypeScript、JavaScript、Python、Java、C#/.NET）を利用できるのが大きな違いになります。

AWS CDK コードはオープンソースです。GitHub の

https://github.com/awslabs/aws-cdk

から入手する事ができます。

==[nonum] AWS CDKのコストは？

AWS CDK に対する追加料金はありません。AWS CDK を使用して作成した AWS リソース (Amazon EC2 インスタンス、Elastic Load Balancing ロードバランサーなど) に対して、手動で作成したのと同じように料金が発生します。
コストは実際に使用した分だけです。最低料金や前払いの義務は発生しません。

==[nonum] AWS CDK CLIについて

AWS CDK CLI を使用すると、CDK アプリケーションを操作することができます。AWS CDK CLI では、AWS CDKアプリで定義されているスタックを一覧表示し、それらのスタックを CloudFormation テンプレートに合成でき、実行中のスタックインスタンスと CDK コードで定義されているスタックの違いを確認でき、AWS の任意のパブリックリージョンにスタックをデプロイできます。
