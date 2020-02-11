= Amazon RDS

//embed[latex]{
\begin{tcolorbox}[colframe=black,colback=white,colbacktitle=black,coltitle=white,coltext=black,title=どんなサービス？,sharp corners]
Amazon RDSとはAmazon Relational Database Serviceの略で、分散リレーショナルデータベースサービスになります。
Amazon RDSは、Amazon Aurora、PostgreSQL、MySQL、MariaDB、Oracle データベース、SQL Server など、6 つの使い慣れたデータベースエンジンから選択する事ができます。
\end{tcolorbox}
//}

//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}

==[nonum] どんなサービス？
Amazon RDS(以下RDS)を使用すると、クラウド上のリレーショナルデータベースのセットアップ、オペレーション、スケールが簡単になります。
ハードウェアのプロビジョニング、データベースのセットアップ、パッチ適用、バックアップなどの時間がかかる管理タスクを自動化しながら、コスト効率とサイズ変更可能なキャパシティーを提供します。

==[nonum] 自動バックアップと復元
RDS では、お客様の DB インスタンスの自動バックアップはデフォルトで Amazon S3 に作成され、指定した期間安全に保存されます。
このバックアップは、ユーザーが設定可能な30分間隔の時間に1日1回行われます。

==[nonum] RDSのコストは？
RDSの利用にあたり、初期費用は不要です。作成したデータベースインスタンス1つごとに月額料金が発生します。また、不要になったデータベースインスタンスは簡単に削除できます。

====[nonum] 停止と起動
RDS では、データベースインスタンスを 1 回に最大 7 日間停止し、起動することができます。
これにより、常にデータベースを実行する必要がなくなり、開発/テスト用途でのデータベースの使用が簡単かつ経済的に行えるようになります。

====[nonum] リザーブドインスタンス
RDS リザーブドインスタンスでは、1 年契約または 3 年契約で DB インスタンスを予約でき、DB インスタンスのオンデマンドインスタンス料金に比べて、大幅な割引を受けられます。

==[nonum] セキュリティー
RDS では、AWS Key Management Service (KMS) で管理するキーを使って、データベースを暗号化できます。
RDS 暗号化を使用して実行するデータベースインスタンスでは、基盤となるストレージに保存されるデータが、自動バックアップ、リードレプリカ、スナップショットと同様に暗号化されます。

