= AWS Code シリーズ
サービス：CICD　対象：SRE　デベロッパー　区分：DevOps

//embed[latex]{
\begin{tcolorbox}[title=どんなサービス？,sharp corners]
AWS Code シリーズは、開発エンジニアの継続的デリバリーの環境を構築するためのサービスです。
Code シリーズには CodeCommit、CodeBuild、CodeDeploy、CodePipeline とこれらサービスを一括でまとめられる CodeStar があります。
\end{tcolorbox}
//}


//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}


==[nonum] 概要

CICD サービスは世の中にたくさんありますが、AWS サービスを利用する場合は AWS サービスとの連携がスムーズになります。
特にデプロイサービスである CodeDeploy を利用すると、カナリアデプロイやブルーグリーンデプロイなどリリース時のリスクを
最小限に抑えるリリース方法を簡単に構築できるのでおすすめです。




==[nonum] Code 3兄弟

===[nonum] CodeCommit
CodeCommit は ソースコード管理する完全マネージドな Git リポジトリサービスです。
GitHub や GitLab などと同じく、クラウド上でソース管理を行うことができます。

====[nonum] 料金

アクティブユーザ数によって料金が変わります。


■ 無料枠

・無制限のリポジトリ

・50 GB のストレージ/月

・10,000 回の Git リクエスト/月

期限がないので少人数プロジェクトの場合は無料枠で運用できちゃいます。

■ 料金体系

・無制限のリポジトリ

・アクティブユーザーごとに 10 GB のストレージ/月

・アクティブユーザーごとに 2,000 件の Git リクエスト/月



===[nonum] CodeBuild

CodeBuild はソースコードをビルドし、テストを実行し、デプロイ可能な状態の
パッケージを作成するサービスです。継続的インテグレーションとデリバリーのための
リリースワークフローを作成できます。

====[nonum] 料金
ビルドにかかった時間とビルド用サーバのスペックで料金が変わります。

■ 無料枠

general1.small を 1ヶ月あたり 100 分まで無料で使えます。
この無料枠は期限がないので個人サービスであれば十分無料枠で利用できるでしょう。

■ 料金体系

general1.small(メモリ：3 GB	VCPU：２) 1分あたり 0.005 USD

general1.medium(メモリ：7 GB VCPU：4）1分あたり	0.01  USD

general1.large(メモリ：15 GB VCPU：8）1分あたり	0.02  USD

#@# 更に大規模プロジェクト用に高スペックなビルドサーバが用意されています。詳細は下記リンクをご参考ください。
#@# https://aws.amazon.com/jp/codebuild/pricing/


//embed[latex]{
\clearpage
//}


===[nonum] CodeDeploy 

CodeDeploy は AWS EC2、ECS、Fargate、Lamabda などの様々なコンピューティング
リソースへアプリのデプロイを自動化するサービスです。本番サービスへのデプロイ
を段階的に適応したり、失敗したときはデプロイを停止したり、
ロールバックを自動化したりすることが簡単に設定できます。

====[nonum] 料金

■ 無料枠

Amazon EC2 や AWS Lambda へのデプロイは無料

■ 料金体系

オンプレミスのデプロイに料金がかかります。AWS サービスのデプロイは無料です。

//embed[latex]{
\begin{tcolorbox}[title=コラム：似たようなサービス,sharp corners]
Code シリースを理解する上で似たようなサービスと比較するとわかりやすいです。
CodeCommit は GitHub や GitLab などの Git サービスが近いです。
CodeBuild は CI を自由に設定できるため CircleCI や GitHub Action などの CIツールと同じようなことができます。
CodeDeploy はデプロイサービスなので、Jenkins が近いです。
3rd パーティ製の CICD サービスを使わずに AWS サービスだけで完結できるのがこの Codeシリーズの利点です。

\end{tcolorbox}
//}

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

==[nonum] めんどくさい CICD の設定も CodeStar でおまかせ

更に、これら Code シリーズを一元管理し、CICD 全体を数分で導入できるサービスとして CodeStar があります。 
バラバラに設定していた Code シリーズのサービスを一元管理できます。
チーム全体がセキュアに連携しやすくなり、ソフトウェア開発プロセス全体の進行状況を簡単に追跡することが可能になります。

//embed[latex]{
\clearpage
//}
