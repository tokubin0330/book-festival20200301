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

==[nonum] 機能
Amazon ElastiCacheとはメインメモリキャッシュのデプロイ、運用、スケーリングをクラウド内で簡単に実行できるウェブサービスです。
メモリキャッシングとはメモリ内にデータを格納することで、データへのアクセス時間を短縮する技術です。
データベースを使用せずに高速のメモリ内のキャッシュを使うことで、WEBアプリケーションの向上を図る事ができます。

==[nonum] どんな時に使うの？
Amazon ElastiCacheの用途として、Amazon RDSと併用して、Amazon RDSへのクエリ結果をAmazon ElastiCacheにキャッシュさせ、キャッシュがある場合はAmazon ElastiCacheのキャッシュを使う。
キャッシュが無い場合のみRDSにAmazon DBアクセスという使い方があります。

==[nonum] Amazon ElastiCacheのコストは？
Amazon ElastiCache に前払い料金は必要ありません。オンデマンドノードなので、消費したリソースのみについて時間単位でお支払いいただきます。

==[nonum] MemcachedとRedis
ElastiCacheは、KVS型のnoSQLであるMemcachedとRedisのプロトコルに準拠しているので、幅広い用途に使うことができます。
インメモリキャッシュエンジンであるMemchaedとRedisをサポートしていますので、WEBアプリケーションの構成や用途に応じて、RedShiftを導入することが可能です。

・Redis

シングルスレッドで動作、データを永続化可能。
Redisの場合はクラスタ構成を組める事ができるので、フェイルオーバー等が簡単になります。

・Memcached

マルチスレッドで動作します、データを永続化できません。