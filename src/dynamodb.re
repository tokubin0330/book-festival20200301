= Amazon DynamoDB
キーワード：NoSQL/キーバリュー型/JSON/ドキュメント型データベース/IoT向け
//embed[latex]{
\begin{tcolorbox}[colframe=black,colback=white,colbacktitle=black,coltitle=white,coltext=black,title=どんなサービス？,sharp corners]
Amazon DynamoDBはマネージド型のNoSQLデータベースになります。Amazon DynamoDB は、規模に関係なく数ミリ秒台のパフォーマンスを実現する事ができます。
Amazon DynamoDB ではデータを JSON 形式で保存しています。この特性をドキュメント型データベースといいます。
\end{tcolorbox}
//}

//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}

==[nonum] どんな時に使うの？
低レイテンシーなデータアクセスが必要なモバイル、ウェブ、ゲーム、広告技術、IoT、およびその他のアプリケーションのキー値とドキュメントのデータベースとして、Amazon DynamoDBを使用しています。
ゲーム業界の企業は、ゲームの状態、プレイヤーのデータ、セッション履歴、リーダーボードを含むゲームプラットフォームのすべての機能にAmazon DynamoDBを使用しています。

これらの企業がAmazon DynamoDBから得られる主な利点は、1桁のミリ秒単位で測定される一貫した低レイテンシーを確実にしながら、何百万もの同時ユーザーおよび要求に合わせて確実にスケールできるということです。

==[nonum] Amazon DynamoDBはサーバレス
Amazon DynamoDB はサーバーレスであり、プロビジョニング、パッチ適用、管理するサーバーはなく、インストール、保守、運用するソフトウェアもありません。

Amazon DynamoDB はテーブルを自動的にスケールアップ/ダウンして容量を調整し、パフォーマンスを維持します。
可用性とフォールトトレランス機能が組み込まれているため、こうした機能のためにアプリケーションを構築する必要はありません。

==[nonum] データの復元
Amazon DynamoDBでは、オンデマンドバックアップ機能を使用する事ができます。この機能によってテーブルの完全なバックアップを作成する事ができます。

Amazon DynamoDBテーブルのデータは、コンソールをワンクリックする事によって、バックアップ及び復元する事ができます。

==[nonum] Amazon DynamoDB のコストは？
Amazon DynamoDBでは、Amazon DynamoDB テーブル内のデータの読み取り、書き込み、保存に加え、ユーザーが有効化したオプション機能が課金の対象となります。

==[nonum] Amazon DynamoDB のTTL機能
Amazon DynamoDBのTTL（Time to Live）機能は、レコード毎にデータの有効期限を指定をする事によって、その有効期限を過ぎるとデータが自動削除されるという機能になります。

この機能を利用する事によって、日々がデータがストアされるようなアプリケーションを実装する時に不要になったデータをテーブルから削除する事ができます。
