= Amazon DynamoDB

//embed[latex]{
\begin{tcolorbox}[colframe=black,colback=white,colbacktitle=black,coltitle=white,coltext=black,title=どんなサービス？,sharp corners]
Amazon DynamoDBはマネージド型のNoSQLデータベースになります。Amazon DynamoDB は、規模に関係なく数ミリ秒台のパフォーマンスを実現する事ができます。
Amazon DynamoDB は、1日に10兆件以上のリクエストを処理することができ、毎秒 2,000 万件を超えるリクエストをサポートします。
\end{tcolorbox}
//}

//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}

==[nonum] 概要
Amazon DynamoDBはNoSQLのデータベースです、その名の通りSQLを使わないデータベースになります。
DynamoDBではデータをJSON形式で保存しています。単純にJSON形式のテキストではなくJSON形式のデータでの保存になります。この特性をドキュメント型データベースといいます。

==[nonum] どんな時に使うの？
低レイテンシーなデータアクセスが必要なモバイル、ウェブ、ゲーム、広告技術、IoT、およびその他のアプリケーションのキー値とドキュメントのデータベースとして、Amazon DynamoDBを使用しています。
ゲーム業界の企業は、ゲームの状態、プレイヤーのデータ、セッション履歴、リーダーボードを含むゲームプラットフォームのすべての機能にAmazon DynamoDBを使用しています。
これらの企業がAmazon DynamoDBから得られる主な利点は、1桁のミリ秒単位で測定される一貫した低レイテンシーを確実にしながら、何百万もの同時ユーザーおよび要求に合わせて確実にスケールできるということです。

==[nonum] Amazon DynamoDBはサーバレス
Amazon DynamoDB はサーバーレスであり、プロビジョニング、パッチ適用、管理するサーバーはなく、インストール、保守、運用するソフトウェアもありません。
Amazon DynamoDB はテーブルを自動的にスケールアップ/ダウンして容量を調整し、パフォーマンスを維持します。
可用性とフォールトトレランス機能が組み込まれているため、こうした機能のためにアプリケーションを構築する必要はありません。

==[nonum] Amazon DynamoDBの無料利用枠
AWS 無料利用枠は、お客様が AWS のサービスを無料で実際に体験できるように設定されています。AWS 無料利用枠の一部として、DynamoDB では以下の特典がご利用いただけます。
各特典は、各リージョンで支払人アカウントごとに月単位で計算されます。

・25 GB のデータストレージ
・DynamoDB ストリームからのストリーム読み込みリクエスト 250 万回
・AWS のサービス全体での合計データ転送 (アウト) 1 GB


