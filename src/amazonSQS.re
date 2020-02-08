= Amazon SQS

//embed[latex]{
\begin{tcolorbox}[colframe=black,colback=white,colbacktitle=black,coltitle=white,coltext=black,title=どんなサービス？,sharp corners]
Amazon SQSとはAmazon Simple Queue Serviceの略になります。完全マネージド型のメッセージキューイングサービスで、マイクロサービス、分散システム、およびサーバーレスアプリケーションの切り離しとスケーリングが可能です。
\end{tcolorbox}
//}

//image[illust][][scale=0.95]{
//}

//embed[latex]{
\clearpage
//}

==[nonum] 概要
Amazon SQSでは基本的に、キューに届いた順序通りにメッセージをクライアントに渡しますが、その順序性はベストエフォートです。FIFO（先入れ先出し）は保証しません。

メッセージの順序性を保つ必要があるなら、メッセージにタイムスタンプやシーケンシャル番号を付与したうえで並べ替えるといった機能を、送信側・受信側のクライアントに付加します。

==[nonum] Amazon SQSの使い方

SQSではメッセージの送信、受信側での処理は以下のような流れになります。
使い方はとてもシンプルで、送信側でメッセージを送り、受信側でメッセージの受信を待機するだけです。

====[nonum]　送信側
1. 指定したキュー名のキューオブジェクトを作る

2. メッセージを送る

====[nonum]　受信側
1. 指定したキュー名のキューオブジェクトを作る

2. メッセージの待機

3. メッセージを受け取ったら処理

4. メッセージを削除

==[nonum] Amazon SQSのコストは？
Amazon SQS は無料で始めることができます。すべてのお客様は、毎月 Amazon SQS リクエストを 100 万件まで無料で行えます。
一部のアプリケーションは、この無料利用枠内で運用できる場合があります。 

==[nonum] Amazon SQSのメリットは？

Amazon SQS では、メッセージキューの管理のために独自のソフトウェアを構築したり、市販またはオープンソースのメッセージキューイングシステムを使用してシステムの開発や設定の初期作業に多くの時間を費やしたりする必要がありません。

また、Amazon SQS はメッセージの耐久性が非常に高いため、お客様や関係者に安心してお使いいただけます。
