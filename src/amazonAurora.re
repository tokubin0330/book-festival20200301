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


==[nonum] 概要
Amazon Auroraとはクラウドネイティブなリレーショナルデータベースエンジンです。高性能でMySQLの最大で5倍、PostgreSQLの2倍のスループットを実現する事ができます。

Amazon AuroraとAmazon RDSの違いは、Amazon RDSはMySQL、PostgreSQL、MariaDB、Orable、SQL Serverを使えるのに対してAmazon Auroraが互換性を持つのはMySQLとPostgreSQLのみです。

また、仮にMySQLやPostgreSQLを使う場合でも、使えるメジャーバージョンがRDSとAuroraでは異なります。

==[nonum] 高可用性と耐久性
Amazon Auroraは3つのアベイラビリティーゾーンにわたってユーザーのデータを6個レプリケーションし、継続的にAmazon S3にバックアップすることで、可用性が99.99%を超えるように設計されています。

物理ストレージの障害は透過的に復旧され、インスタンスのフェイルオーバーは通常30秒未満で完了します。

==[nonum] Amazon Auroraのユースケース

====[nonum]　エンタープライズアプリケーション
Amazon Aurora は、リレーショナルデータベースを使用するあらゆるエンタープライズアプリケーションにとってすばらしい選択肢です。

商業用データベースに比べて、Amazon Aurora はデータベースコストを 90% 以上削減することが可能であり、さらに、データベースの信頼性と可用性も向上します。

====[nonum]　ウェブゲームとモバイルゲーム
きわめて大規模なスケールで動作するように構築されているウェブゲームとモバイルゲームは、高スループット、大規模ストレージスケーラビリティ、および高可用性を備えたデータベースを必要とします。

Amazon Auroraは、このような要件の厳しいアプリケーションのニーズを、将来の成長に対する余力を持ちながら、満たすことができます。Amazon Aurora にはどのようなライセンス制約もないので、これらのアプリケーションが持つさまざまな使用パターンに完全に適合します。

//embed[latex]{
\clearpage
//}

====[nonum]　Software as a Service (SaaS) アプリケーション
SaaS アプリケーションでは、多くの場合、マルチテナントのアーキテクチャが使用されます。このアーキテクチャでは、インスタンスとストレージのスケーリングにきわめて高いレベルの柔軟性が求められ、さらに、高パフォーマンスと高信頼性も求められます。

Amazon Aurora は、マネージド型データベースサービスでこれらの機能のすべてを提供します。


==[nonum] Amazon Auroraのコストは？

Amazon Auroraは、使用した分のみ料金が発生し、初期費用は必要ありません。最低料金設定はありません。別途記載がない限り、以下の料金は Amazon Aurora の MySQL 互換エディションと PostgreSQL 互換エディションの両方に適用されます。