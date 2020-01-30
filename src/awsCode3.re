= AWS Code シリーズ
サービス：CICD、対象：SRE、デベロッパー　、区分：DevOps

//embed[latex]{
\begin{tcolorbox}[title=どんなサービス？,sharp corners]
AWS Code シリーズは、開発エンジニアの継続的デリバリーの環境を構築するためのサービスです。
Code シリーズには CodeCommit、CodeBuild、CodeDeploy、CodePipeline とこれらサービスを一括でまとめられる CodeStar があります。
\end{tcolorbox}
//}


//image[illust][][scale=0.80]{
//}



CICD サービスは世の中にたくさんありますが、AWS サービスを利用する場合は AWS サービスとの連携がスムーズになります。
特にデプロイサービスである CodeDeploy を利用すると、カナリアデプロイやブルーグリーンデプロイなどリリース時のリスクを
最小限に抑えるリリース方法を簡単に構築できるのでおすすめです。


//embed[latex]{
\clearpage
//}

==[nonum] 似たようなサービス




==[nonum] Code 3兄弟

===[nonum] CodeCommit
CodeCommit は ソースコード管理する完全マネージドな Git リポジトリサービスです。
GitHub や GitLab などと同じく、クラウド上でソース管理を行うことができます。

===[nonum] CodeBuild

CodeBuild はソースコードをビルドし、テストを実行し、デプロイ可能な状態の
パッケージを作成するサービスです。継続的インテグレーションとデリバリーのための
リリースワークフローを作成できます。

===[nonum] CodeDeploy 

CodeDeploy は AWS EC2、ECS、Fargate、Lamabda などの様々なコンピューティング
リソースへアプリのデプロイを自動化するサービスです。本番サービスへのデプロイ
を段階的に適応したり、失敗したときはデプロイを停止したり、
ロールバックを自動化したりすることが簡単に設定できます。

//embed[latex]{
\clearpage
//}

==[nonum] Code 3兄弟を束ねる CodePipeline

CodePipeline は継続的デリバリーサービスであり、アプリケーションや
インフラストラクチャのアップデートのためのワークフローを自動化します。

CodePipeline で設定するワークフローは AWS CLI や CloudFormation で IaC で管理
することができます。アプリケーションをアップデートするためのテスト、
デプロイステップ、依存関係などを簡単に設定することができます。

これらはすべて AWS のフルマネージド型サービスとして提供されているので、
サービスのプロビジョニング、管理、スケーリングは不要です。

//embed[latex]{
\clearpage
//}

==[nonum] めんどくさい CICD の設定も CodeStar でおまかせ

更に、これら Code シリーズを一元管理し、継続的デリバリーのツールチェーンを
テンプレートをもとに数分で導入できるサービスとして CodeStar があります。 
バラバラに設定していた Code シリーズのサービスを一元管理できることでチーム全体が
セキュアに連携しやすくなり、ソフトウェア開発プロセス全体の進行状況を簡単
に追跡することが可能になります。

//embed[latex]{
\clearpage
//}
