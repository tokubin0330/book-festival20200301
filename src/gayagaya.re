= 【特集】AWS Dev Day Challenge優勝サービス「がやがや動画」のすべて

去年の年末、10月29日 ~ 11月2日の5日間にわたりAWSのイベント「AWS Dev Day Tokyo 2018」が開催されました。
5日間というとても大きな規模で開催されたイベントだったので参加された方、記憶に残っている方もたくさんいるかと思います。
そのイベントの最終日の裏番として開催されていたのが、「AWS Dev Day Challenge」というハッカソンイベントでした。
そこに3人の有志で参加し「がやがや動画」という動画サービスを作成しました。
その内容を記録に残したいと思い特集という形で掲載することにしました。@<fn>{attention}

====[column] ちょっと見て！！！
今回雑誌の取材をしていただき、なんとSoftware Design 2019年1月号に写真付きで掲載してもらいました。
定期購読している会社も多いかと思いますので、Software Design 2019年1月号の169ページを改めてチェックしてください！

====[/column]

//footnote[attention][今回、公開にあたってソースコードを一部加筆修正していることをご了承ください。とてもじゃないけどそのままではお見せできませんでした。]

== AWS Dev Day Challengeとは

@<b>{「AWSの各種サービスを駆使して、クールなWebサービスを開発せよ。」}@<br>{}

AWS Dev Day Challengeは、アプリケーションデベロッパーのために世界主要都市で開催されるテクノロジーカンファレンス
AWS Dev Day Tokyo 2018（以下DevDay）内のイベントの一つで、3人1組で行う開発コンテストです。
日本では2018年11月にAWSの目黒オフィスで開かれ、
当日朝に公開されるお題から1つを選びチームで実装、その日の夕方から開催されるDevDayのアフターパーティーで
参加チームが発表を行い、AWSのSA達がアーキテクチャ、ライフサイクル管理、コスト、耐障害性で総合的に1番イケてるものを選び表彰するというものです。

== がやがや動画とは
AWS Dev Day Challengeで作成した「がやがや動画」のコンセプトは、がや感あふれる動画投稿サービスです。
特徴は、

 * スマホを使って動画を投稿
 * 投稿した動画はWEBサイト上にリアルタイムに追加されていき画面が動画で埋め尽くされる
 * 投稿された動画はリピート再生させてがや感をアップ

インパクト重視で、実用性はあまり考えずに自分たちが作っていて楽しいものを目指しました。
というわけで、今後のサービスローンチは今のところありません。

//embed[latex]{
\clearpage
//}

== アーキテクチャの概要

全体的なアーキテクチャはこんな感じで、AWSフルマネージドなサーバーレス構成です。

//image[gayagaya_arch][がやがや動画のアーキテクチャ][scale=1.0]{
//}

//embed[latex]{
\clearpage
//}

== 撮影された動画のアップロード

スマホ側の処理を説明します。

 * CognitoからS3のアクセス権のあるIAM Roleの払い出し
 * 撮影された動画を保存用バケットへアップロード
 

=== IAM & Cognito

Cognitoでスマホ側用にID Poolを作成します。
一時トークンの払い出しのためだけに使用するので、「認証されていないIDに対してアクセスを有効にする」をチェックします。

//image[cognito-idpoolcreate1][動画投稿用Cognito作成1][scale=1.0]{
//}

//image[cognito-idpoolcreate2][動画投稿用Cognito作成2][scale=1.0]{
//}

Cognito作成時に作成された未認証ユーザーのIAMロールに対して、S3のアクセスポリシーをアタッチします。

//image[cognito-iam][動画投稿用のIAM設定][scale=1.0]{
//}

=== S3

動画保存用のgayagayaバケットを作成します。
このバケットはViewerからアクセスされるため、パブリックリードなバケットポリシーを設定します。@<fn>{gayagaya-bucket}

//list[movie_backetpolicy][動画保存用S3のバケットポリシー]{
{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Sid": "AddPerm",
            "Effect": "Allow",
            "Principal": "*",
            "Action": "s3:GetObject",
            "Resource": "arn:aws:s3:::gayagaya/output/*"
        }
    ]
}
//}

また、別バケットからアクセスするのでCORSの設定も行います。

//list[movie_backetcors][動画保存用S3のCORS設定]{
<?xml version="1.0" encoding="UTF-8"?>
<CORSConfiguration xmlns="http://s3.amazonaws.com/doc/2006-03-01/">
<CORSRule>
    <AllowedOrigin>*</AllowedOrigin>
    <AllowedMethod>HEAD</AllowedMethod>
    <AllowedMethod>GET</AllowedMethod>
    <AllowedMethod>PUT</AllowedMethod>
    <AllowedMethod>POST</AllowedMethod>
    <AllowedMethod>DELETE</AllowedMethod>
    <ExposeHeader>ETag</ExposeHeader>
    <AllowedHeader>*</AllowedHeader>
</CORSRule>
</CORSConfiguration>
//}


スマホ表示用のspバケットを作成します。
このバケットはパブリックリードなバケットポリシーを設定します。
githubリポジトリのspディレクトリの中身をアップロードします。@<fn>{upload-file}

//list[sp_backetpolicy][スマホ用S3のバケットポリシー]{
{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Sid": "AddPerm",
            "Effect": "Allow",
            "Principal": "*",
            "Action": "s3:GetObject",
            "Resource": "arn:aws:s3:::sp/*"
        }
    ]
}
//}


//footnote[gayagaya-bucket][バケットポリシーのResourceはバケット名に合わせて適宜変更してください]
//footnote[upload-file][index.htmlファイル内のプールIDとバケット名は環境に合わせて変えてください]

== 動画をGifアニメへ変換

投稿された動画をGifアニメに変換する処理です。

 * S3のPutイベントでLambdaを起動
 * LambdaがTranscorder Pipelineを起動
 * Transcorderが動画をGifアニメへ変換しS3に保存

=== Elastic Transcorder

Transcorderで使うIAMロールはデフォルトのまま、入力のS3バケット名と出力のS3バケット名を指定して作成します。

//image[transcorder-pipeline][Transcorderのパイプライン設定][scale=1.0]{
//}

プリセットはこんな感じでgifアニメーションへ変換するための設定を行います。

//image[transcorder-preset][TranscorderのGif変換用プリセット][scale=1.0]{
//}

=== Lambda

Transcorderを起動するLambdaを作成します。
動画保存用のgayagayaバケットにプレフィックスがinput/のオブジェクトがアップロードされたら、
このLambdaが起動するようにObjectCreatedByPutイベントを設定します。

//image[lambda-totranscorder][Transcorder起動用Lambda][scale=1.0]{
//}

環境変数にはgifファイルを保存するgayagayaバケット名と、先ほど作成したTranscorderのPipeline IDと、Preset IDを指定します。

//image[lambda-totranscorder-env][Transcorder起動用Lambdaの環境変数][scale=1.0]{
//}

//embed[latex]{
\clearpage
//}

LambdaのIAMロールにTranscorderのフルアクセスと、S3のフルアクセスのポリシーをアタッチします。

//image[lambda-totranscorder-iam][Transcorder起動用LambdaのIAM][scale=1.0]{
//}

=== S3

Viewerの画面表示に使うためのViewerバケットです。
こちらもパブリックリードが必要なのでバケットポリシーを設定します。@<fn>{viewer-bucket}
githubリポジトリのviewerディレクトリの中身をアップロードします。@<fn>{upload-file2}

//list[viewer_backetpolicy][Viewer用S3のバケットポリシー]{
{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Sid": "AddPerm",
            "Effect": "Allow",
            "Principal": "*",
            "Action": "s3:GetObject",
            "Resource": "arn:aws:s3:::viewer/*"
        }
    ]
}
//}

//footnote[viewer-bucket][バケットポリシーのResourceはバケット名に合わせて適宜変更してください]
//footnote[upload-file2][viewer/index.htmlファイル内のプールIDとバケット名、IOTエンドポイントは環境に合わせて変えてください]

//embed[latex]{
\clearpage
//}

== Gifアニメの表示

GifアニメをViewer側に表示するまで処理を説明します。

 * S3のPutイベントでLambdaを起動
 * LambdaがIoT CoreのMQTTにパブリッシュ
 * Viewer側はあらかじめIoT CoreのMQTTをサブスクライブしていてパブリッシュされた画像URLをViewerが画面に表示する

#@# Gifアニメへの変換が完了したらMQTTにGif画像のURLをパブリッシュするLambdaを作成します。
#@# フロント側では、そのMQTTのトピックをサブスクライブしておきパブリッシュされたURLで画像を画面に表示します。
#@# IoT CoreのMQTTを利用することでAWSフルマネージドなサーバーレスを実現しているのがポイントです。

=== IoT Core

エンドポイントだけ確認する必要がありますので、IoT Coreのページから設定と進み、
エンドポイントを確認しておきます。

=== Lambda

MQTTにパブリッシュするためのLambdaを作成します。
動画保存用のgayagayaバケットにプレフィックスがoutput/のオブジェクトが作成されたら、
このLambdaが起動するようにObjectCreatedイベントを設定します。

//image[lambda-publish][MQTTへパブリッシュするLambda][scale=1.0]{
//}

環境変数には先程の、IoTエンドポイントと、パブリッシュするMQTTのトピック名を設定します。

//image[lambda-publish-env][MQTTへパブリッシュするLambdaの環境変数][scale=1.0]{
//}

//embed[latex]{
\clearpage
//}

このLambdaで利用するIAMロールにはIoTFullAccessのポリシーをアタッチしておきます。

//image[lambda-publish-iam][MQTTへパブリッシュするLambdaのIAM][scale=1.0]{
//}

=== IAM & Cognito

CognitoでViewer側用にID Poolを作成します。設定は動画投稿用と同じです。
こちらのCognitoの未認証ユーザーに付与するロールには、S3のポリシーとIoTのポリシーをアタッチします。

//image[cognito-viewer-iam][MQTTをサブスクライブするためのIAM][scale=1.0]{
//}

//embed[latex]{
\clearpage
//}

== プレゼン資料の準備

残り1時間というところでサービスは完成しました。
あとはプレゼン資料の作成です。
実は、この時間になる少しからメンバーの1人が自分の作業を終えていて、空いた手でプレゼン資料のたたき台を作成し始めていました。
ここら辺の言われなくても勝手にやる適な連携は気持ちがいいものでした。後は、3人であれやこれやとつめていくだけです。
プレゼンの時間はわずか3分間、この短い時間でがやがや動画の魅力を伝えなければいけません。
というより、何を作ったのか認識してもらう必要がります。

そこで、私たちが注意した点は以下の5点です。

 * 時間がないので、プレゼン資料の枚数は限りなく少なくする
 * 時間がないので、すべてを伝えることはあきらめる
 * 時間がなくても、絶対にデモを動かす
 * 時間がなくても、自己紹介で笑いをとる
 * 1発勝負なので、リハーサルを何度もおこなう

そうして作成したプレゼン資料がこちらです。

@<href>{https://github.com/takaaki-s/gayagaya-movie}

== ソースコード大公開！

がやがや動画のソースコードはgithubで公開していますので、MITライセンスの元ご自由にお使いください。

@<href>{https://github.com/takaaki-s/gayagaya-movie}

== まとめ

実は、開発途中から気が付いていたのですが、動画ファイルをgifアニメーションに変換するとファイル容量が大きくなる。とてつもなく大きくなる。
そこで、大きくなったファイルを少しでも小さくするために画質を落とす。これでもかというくらいに落としまくる。。。
いやー、動画投稿サイトのくせに画質がちょー悪い！（笑
というわけで、まとめです。

そもそもコンセプトが間違ったのかな！！(・ω≦) ﾃﾍﾍﾟﾛ

おしまい。
