= Amazon S3

//embed[latex]{
\begin{tcolorbox}[colframe=black,colback=white,colbacktitle=black,coltitle=white,coltext=black,title=どんなサービス？,sharp corners]
AWSの記念すべき最初のサービス！！！どこからでも好きなだけ様々なファイルを保存する事ができるストレージサービスです！！
99.999999999％の高い耐久性と高いコスト効率が売り！！！Amazon S3 のウェブサービスを利用すれば、インターネットストレージを使用するアプリケーションを簡単に構築することができます！！
\end{tcolorbox}
//}

//image[sample1][][scale=0.95]{
//}


//embed[latex]{
\clearpage
//}


==[nonum] 概要
Amazon S3はAmazon Simple Storage Serviceの略になります。
Amazon S3の特徴としては、データを3箇所以上に冗長化して保存されるので99.999999999% という高い耐久性が実現できます。
また容量の制限はありません。ただし1つのファイルサイズは5TBまでという制限があります

==[nonum] どんな時に使うの？
画像やhtmlファイル等の静的コンテンツの保存先及び、配信やログ保存用やアプリケースションのストレージとして利用する事ができます。
また、サーバのバックアップとしても使われる事もあります。

==[nonum] データの復元ができる！
Amazon S3にはバージョニングという機能があります。
この機能を使用する事によって、謝って削除してしまったデータ等を復元する事ができます。

==[nonum] Amazon S3 のコストは？
Amazon S3 では、実際に使用した分のみ料金が発生します。最低料金設定はありません。
AWS 無料利用枠でAWS GovCloud リージョンを除くすべてのリージョンで Amazon S3 の使用を無料で開始していただけます。
AWS の新規お客様は、Amazon S3 標準ストレージ 5 GB、20,000 Get リクエスト、2,000 Put リクエスト、データ受信 (イン) 15 GB 、データ送信 (アウト) 15 GB を毎月 1 年間ご利用いただけます。

==[nonum] 一緒に使われるサービス
Amazon S3と関連するサービスとしてはCloudFrontがあげられます。CloudFrontはCDN(キャッシュ)のサービスです。
コンテンツを海外に配信する場合や、国内でも大量のデータを配信する場合などに利用します。

また、Lambda を使用してAmazon S3からの通知を処理することができます。オブジェクトが作成または削除されたときに、イベントを Amazon S3 から Lambda 関数に送信できます。

