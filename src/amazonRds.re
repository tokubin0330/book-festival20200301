= Amazon RDS
キーワード：マネージド型/リードレプリカ/リードレプリカ
//embed[latex]{
\begin{tcolorbox}[colframe=black,colback=white,colbacktitle=black,coltitle=white,coltext=black,title=どんなサービス？,sharp corners]
Amazon RDSとはAmazon Relational Database Serviceの略で、マネージド型のリレーショナルデータベースサービスになります。
Amazon RDSは、Amazon Aurora、PostgreSQL、MySQL、MariaDB、Oracle データベース、SQL Server など、6 つの使い慣れたデータベースエンジンから選択する事ができます。
\end{tcolorbox}
//}

//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}

==[nonum] 自動バックアップと復元
Amazon RDS では、DB インスタンスの自動バックアップはデフォルトで Amazon S3 に作成され、指定した期間安全に保存されます。
このバックアップは、ユーザーが設定可能な30分間隔の時間に1日1回行われます。

==[nonum] RDSのコストは？
Amazon RDSの利用にあたり、初期費用は不要です。作成したデータベースインスタンス1つごとに月額料金が発生します。また、不要になったデータベースインスタンスは簡単に削除できます。

==[nonum] 自動フェイルオーバーについて
マスターのAmazon RDSに障害が発生した場合、自動的にスレーブへフェイルオーバーを行います。
これはユーザー側ではオペレーションは不要です。データは、マスターとスレーブで常に同期されているため、リカバリの必要はありません。

==[nonum] リードレプリカ
マスターデータベースと同じデータベースを複製して、読み取り専用として構築したものをリードレプリカといいます。
リードレプリカを利用することによって、読み取り頻度の高いデータベースを増設できるため、パフォーマンスを向上させることができます。

==[nonum] セキュリティー
Amazon RDS では、AWS Key Management Service (KMS) で管理するキーを使って、データベースを暗号化できます。
Amazon RDS 暗号化を使用して実行するデータベースインスタンスでは、基盤となるストレージに保存されるデータが、自動バックアップ、リードレプリカ、スナップショットと同様に暗号化されます。

