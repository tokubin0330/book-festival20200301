= Amazon ElastiCache

//embed[latex]{
\begin{tcolorbox}[colframe=black,colback=white,colbacktitle=black,coltitle=white,coltext=black,title=どんなサービス？,sharp corners]
Amazon ElastiCacheは、MemcachedまたはRedisプロトコルに準拠するサーバーノードのデプロイと実行をクラウド内で簡単に実行できるウェブサービスです。
なお、ElastiCacheのスペルはCを2個つける間違いがあるので注意しましょう。
\end{tcolorbox}
//}

//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}

==[nonum] どんなサービス？
Amazon ElastiCacheとはメインメモリキャッシュのデプロイ、運用、スケーリングをクラウド内で簡単に実行できるウェブサービスです。
メモリキャッシングとはメモリ内にデータを格納することで、データへのアクセス時間を短縮する技術です。
データベースを使用せずに高速のメモリ内のキャッシュを使うことで、WEBアプリケーションの向上を図る事ができます。

==[nonum] どんな時に使うの？
Amazon ElastiCacheの用途として、Amazon RDSと併用して、Amazon RDSへのクエリ結果をAmazon ElastiCacheにキャッシュさせ、キャッシュがある場合はAmazon ElastiCacheのキャッシュを使う。
キャッシュが無い場合のみRDSにAmazon DBアクセスという使い方があります。

==[nonum] Amazon ElastiCacheのコストは？
お客様が使用した分に対してのみお支払いいただきます。最低料金はありません。料金はノードタイプごとに使用されたノード時間単位となります。
1 時間未満のノード使用時間は 1 時間分として請求されます。同じアベイラビリティーゾーン内での Amazon EC2 と Amazon ElastiCache間のデータ転送は無料です。
同じリージョンの異なるアベイラビリティーゾーンにある Amazon EC2インスタンスと Amazon ElastiCacheノード間でデータを転送する場合は、標準の Amazon EC2 リージョン内データ転送料金が適用されますが、Amazon EC2 インスタンスについては、データの着信/発信に対してのみ課金されます。

==[nonum] MemcachedとRedis
ElastiCacheは、KVS型のnoSQLであるMemcachedとRedisのプロトコルに準拠しているので、幅広い用途に使うことができます。
インメモリキャッシュエンジンであるMemchaedとRedisをサポートしていますので、WEBアプリケーションの構成や用途に応じて、RedShiftを導入することが可能です。

・Redis

シングルスレッドで動作、データを永続化可能。
Redisの場合はクラスタ構成を組める事ができるので、フェイルオーバー等が簡単になります。

・Memcached

マルチスレッドで動作します、データを永続化できません。