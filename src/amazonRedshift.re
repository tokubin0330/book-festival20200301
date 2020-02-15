= Amazon Redshift
キーワード：データウェアハウス/列志向/スナップショット
//embed[latex]{
\begin{tcolorbox}[colframe=black,colback=white,colbacktitle=black,coltitle=white,coltext=black,title=どんなサービス？,sharp corners]
Amazon Redshiftとは、AWSが提供するクラウド型データウェアハウス(DWH)サービスです。数百ギガバイトのデータから開始して、ペタバイト以上まで拡張できます。
\end{tcolorbox}
//}

//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}


==[nonum] Amazon Redshiftの機能
Amazon Redshiftは、データウェアハウスを設定、操作、および拡張するためのすべての作業を管理します。
これらのタスクには、クラスターの容量のプロビジョニング、モニタリング、およびバックアップのほか、Amazon Redshiftエンジンへのパッチおよびアップグレードの適用が含まれます。

RDBMSとは違って、継続的な書き込みや更新には向いておらず、一括でデータを書き込み分析のため大容量データを読み出すという処理に最適化されています。Amazon Redshiftでは、大量のデータを短時間で読み出し・分析することが可能です。

Amazon Redshiftの特徴として、列志向型データベースという点があります。MySQLのようなリレーショナルデータベースはデータを行（レコード）単位で保持している事に対し、Redshiftは列単位で保持しています。

Amazon Redshiftは列志向にして並列にクエリを実行するので集計が得意という特徴があります。

Amazon Redshiftは、「PostgreSQL 8.0.2」に準拠しています。PostgreSQL標準の「クライアントコマンド」「psql」を使用可能で、JDBCやODBCなどの接続もサポートしています。

==[nonum] Amazon Redshiftのコストは？

Amazon Redshift は、他のどのデータウェアハウスを運用するよりも低コストです。
1時間あたりわずか 0.25 USD で開始し、ペタバイト単位のデータと数千人の同時ユーザーに対応できるようにスケールアップできます。ビジネスニーズにぴったり合ったものを選ぶことができ、コンピューティングを過剰にプロビジョニングすることなくストレージを増大させる能力と、ストレージのコストを増やすことなくコンピューティング性能を増強する柔軟性を備えています。

Amazon Redshiftは従来のデータウェアハウス構築と比較すると、年間費用で10倍～1000倍近くのコストダウンを見込む事ができます。

==[nonum] どんな時に使うの？
Amazon Redshiftは大量データの保持、データウェアハウス、BIツールなどの分析に向いています。
Amazon Redshiftは列指向のアーキテクチャになっているため、データの集計・分析に大変向いています。