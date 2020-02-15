= Amazon ElastiCache

//embed[latex]{
\begin{tcolorbox}[colframe=black,colback=white,colbacktitle=black,coltitle=white,coltext=black,title=どんなサービス？,sharp corners]
Amazon ElastiCacheは、マネージド型のインメモリデータベースです。メモリ上で処理を実行するため、高スループットかつ低レイテンシーな処理を実現できます。
なお、ElastiCacheのスペルはCを2個つける間違いがあるので注意しましょう。
\end{tcolorbox}
//}

//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}

==[nonum] 機能
マスターのElastiCacheに障害が発生した場合は、自動的にスレーブへフェイルオーバーを行います。挙動としてはRDSと同様にスレーブのElastiCacheをマスターに昇格させます。
なお、フェイルオーバー中はわずかにタイムダウンが発生します。

==[nonum] どんな時に使うの？
Amazon ElastiCacheの用途として、Amazon RDSと併用して、Amazon RDSへのクエリ結果をAmazon ElastiCacheにキャッシュさせ、キャッシュがある場合はAmazon ElastiCacheのキャッシュを使う。
キャッシュが無い場合のみRDSにAmazon DBアクセスという使い方があります。

==[nonum] Amazon ElastiCacheのコストは？
Amazon ElastiCache に前払い料金は必要ありません。オンデマンドノードなので、消費したリソースのみについて時間単位でお支払いいただきます。

==[nonum] MemcachedとRedis
ElastiCacheは、キーバリュー型のNoSQLデータベースサービスになります。インメモリキャッシュエンジンであるMemchaedとRedisをサポートしていますので、WEBアプリケーションの構成や用途に応じて、RedShiftを導入することが可能です。

・Redisについて

シングルスレッドで動作、データを永続化可能。Redisの場合はクラスタ構成を組める事ができるので、フェイルオーバー等が簡単になります。

・Memcachedについて

マルチスレッドで動作します、データを永続化できません。