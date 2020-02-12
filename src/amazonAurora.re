= Amazon Aurora

//embed[latex]{
\begin{tcolorbox}[colframe=black,colback=white,colbacktitle=black,coltitle=white,coltext=black,title=どんなサービス？,sharp corners]
Amazon Aurora は、MySQL および PostgreSQL と互換性のあるクラウド向けのリレーショナルデータベースであり、従来のエンタープライズデータベースのパフォーマンスと可用性に加え、
オープンソースデータベースのシンプルさとコスト効率性も兼ね備えています。
\end{tcolorbox}
//}

//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}


==[nonum] どんなサービス？
Amazon Auroraとはクラウドネイティブなリレーショナルデータベースエンジンです。高性能でMySQLの最大で5倍、PostgreSQLの2倍のスループットを実現する事ができます。

Amazon AuroraとAmazon RDSの違いは、Amazon RDSはMySQL、PostgreSQL、MariaDB、Orable、SQL Serverを使えるのに対してAmazon Auroraが互換性を持つのはMySQLとPostgreSQLのみです。

また、仮にMySQLやPostgreSQLを使う場合でも、使えるメジャーバージョンがRDSとAuroraでは異なります。

==[nonum] 高可用性と耐久性
Amazon Auroraは3つのアベイラビリティーゾーンにわたってユーザーのデータを6個レプリケーションし、継続的にAmazon S3にバックアップすることで、可用性が99.99%を超えるように設計されています。

物理ストレージの障害は透過的に復旧され、インスタンスのフェイルオーバーは通常30秒未満で完了します。


==[nonum] Amazon Auroraのコストは？

Amazon Auroraは、使用した分のみ料金が発生し、初期費用は必要ありません。最低料金設定はありません。