= AWS Amplify Predictionsで始めるAI/ML入門

== はじめに
AWS AmplifyはAWSのサービスを使用して簡単にアプリケーション開発を始められるサービスです。私はAWS Amplifyを開発で使用したりブログなどで紹介していますが、日々需要が高まってきていることを感じます。

今回は2019年に追加された機能「Predictions」を活用した AI/MLサービスの開発をご紹介したいと思います。


== AWS Amplifyについておさらい
AWSが提供するBaaS+UIサービスです。解析/API/認証/通知/ストレージ/チャットボットなどを提供しています。AWSが開発している各種サービス(Amazon S3/Amazon Cognitoなど)を簡単に扱う手段をAWS Amplifyが提供しているとイメージしてください。

また似たような名称でAWS Amplify Consoleというサービスがありますがこちらは「デプロイを簡単にするサービス」で、今回のものと若干違いますのでご注意ください。

それぞれのサービスについて私のブログで紹介しておりますので、詳しく知りたい方はご覧ください。

== Predictionsの機能について
今回紹介するAWS Amplifyの機能であるPredictionsですが、こちらも他のAWS Amplifyの機能と同様にAWSのAI系サービスを裏側で使っています。

 * Amazon Translate(翻訳)
 * Amazon Polly(音声変換)
 * Amazon Transcribe(音声認識)
 * Amazon Rekognition(画像・動画分析)
 * Amazon Textract(OCR+構造化データ抽出)
 * Amazon Comprehend(自然言語処理)

なぜこのような説明をしているかというと、AWS Amplifyでは簡単にアプリケーションを開発できますが、一方複雑なアプリケーションを作ろうと思うと裏側で使用しているサービスを調べることも多いので、どのようなサービスを使っているのかを把握しておく必要があるからです。

== 環境構築
開発を行うにあたり、環境構築を行います。事前にAWS IAMでユーザーを作成してください。「プログラムによるアクセス」ができる権限のみあれば問題ありません。またAIの各種サービスを使用しますので管理者権限に近い状態が望ましいです。

=== Reactアプリ作成とAWS Amplifyの初期設定
今回はReactを利用してアプリ開発を行いますので、必要なコマンドを実行します。
//cmd{
$ npm install -g create-react-app
$ create-react-app myapp && cd myapp
$ npm start
//}

//cmd{
$ amplify init
//}


=== Predictionsの追加
次はAWS Amplifyの追加とPredictionsの追加を行います。

//cmd{
$ amplify add predictions
//}
add predictionsを行うといくつか対話的に質問が行われます。

//cmd{
? Please select from of the below mentioned categories 
> Convert

? What would you like to convert?
> Generate speech audio from text

? Select a speaker
> Mizuki
//}

またこちらのインストールも忘れずに行ってください。
//cmd{
$ yarn add aws-amplify
//}

addコマンドを実行するとCLIでいくつかの質問をされます。全て完了したらCLI上でpushしましょう。
//cmd{
$ amplify push
//}

App.jsに以下のようなコードを追加します

//listnum[init][App.js][js]{
import Amplify from '@aws-amplify/core';
import Predictions, { AmazonAIPredictionsProvider } from '@aws-amplify/predictions';
import awsconfig from './aws-exports';

Amplify.configure(awsconfig);
Amplify.addPluggable(new AmazonAIPredictionsProvider());
//}

== AIサービスの開発を行う
Presictionsの機能を使って開発を行ってみましょう。それぞれのサンプルコードはGitHubにアップロードしておきます。

=== テキストから音声に変換
この機能はAmazon Pollyを利用します。上記の環境構築で文字から音声変換を行う準備は整いました。次はプログラムを行います。

//listnum[converttext][ConvertText][js]{
    Predictions.convert({
      textToSpeech: {
        source: {
          text: textToGenerateSpeech,
        },
      }
    }).then(result => {
      }, (err) => console.log({err}));
    })
      .catch(err => setResponse(err))
//}
声についてはCLIで作成時に選択した音声がデフォルトになりますが、プログラム上で変更することも可能です。

//listnum[converttext2][ConvertText2][js]{
      textToSpeech: {
        source: {
          text: textToGenerateSpeech,
        },
        voiceId: "Mizuki" //もしくは別の声 
      }
//}

声の一覧はこちらからご覧になれます。
https://docs.aws.amazon.com/polly/latest/dg/voicelist.html

プログラムが完了したらローカルで実行してみましょう。

//cmd{
$ npm start
//}

簡単に音声がでませんでしたか？

=== テキスト翻訳機能を追加する
次はテキストの翻訳を行います。この機能はAmazon Translateを利用しています。
AWS Amplifyでは新しいAI系サービスを追加するごとにコマンド入力が必要になります。

//cmd{
$ amplify add predictions

? Please select from of the below mentioned categories 
> Convert

? What would you like to convert?
> Translate text into a different language

#以下は日本語から英語に変換する場合の例です
? What is the source language?
> Japanese

? What is the target language?
> English

$ amplify push
//}

次はプログラムを行います。
//listnum[translatettext][Translate][js]{
    Predictions.convert({
      translateText: {
        source: {
          text: textToTranslate,
          // language : "es" // defaults configured on aws-exports.js
          // supported languages https://docs.aws.amazon.com/translate/latest/dg/how-it-works.html#how-it-works-language-codes
        },
        // targetLanguage: "en"
      }
    }).then(result => setResponse(JSON.stringify(result, null, 2)))
      .catch(err => setResponse(JSON.stringify(err, null, 2)))
//}

この状態で「こんにちは」と入力すると、resultには
{"text":"Hello","language":"en"}
とオブジェクトが出力されます。

====[column]React.jsの補足
setResponseという関数がありますが、これは「ステートフック」という機能です。関数コンポーネントにstateの機能を追加することができます。
====[/column]

=== テキスト翻訳と音声変換を組み合わせる
これまでの章で2つの「音声変換」「翻訳」の2つのAIサービスを作成しました。
次はこれら2つのサービスを組み合わせて、翻訳サービスを作ってみましょう。

 1. テキスト入力
 2. 英語に翻訳
 3. 翻訳した文章を音声で出力

先ほどのプログラムでは音声の出力がMizukiという日本人女性の声になっていますので、英語の発音がよくありません。これを解決するためにVoiceIdの変更を行います。

//listnum[translatespeechtext][TranslateAndSpeech][js]{
  function generateTextToSpeech(text) {
    Predictions.convert({
      textToSpeech: {
        source: {
          text: text,
        },
        voiceId: "Amy", //ここが重要です 
      }
    }).then(result => {
      let AudioContext = window.AudioContext || window.webkitAudioContext;
      const audioCtx = new AudioContext(); 
      const source = audioCtx.createBufferSource();
      audioCtx.decodeAudioData(result.audioStream, (buffer) => {
        source.buffer = buffer;
        source.connect(audioCtx.destination);
        source.start(0);
      }, (err) => console.log({err}));
      
    })
      .catch(err => setResponse(err))
  }
//}

二つのコードを組み合わせるだけでAIサービスを開発できるのでとても便利ですね。

=== 画像からラベル付けをおこなう
先ほどまでは変換を行いました。次は画像識別(Identify)にチャレンジしたいと思います。
画像のラベル付けは「与えられた画像に対してどこに何が写っているかを識別しその物体の名称と矩形を返す」機能です。

早速試してみましょう。
//cmd{
$ amplify add predictions

? Please select from of the below mentioned categories 
> Identify

? Please select from of the below mentioned categories 
> Identify Labels

$ amplify push
//}

プログラムについては先ほどと同様に追加します。

//listnum[imagelabeling][LabelImage][js]{
Predictions.identify({
      labels: {
        source: {
          file,
        },
        type: "ALL"
      }
    }).then(result => setResponse(JSON.stringify(result, null, 2)))
      .catch(err => setResponse(JSON.stringify(err, null, 2)))
//}

この機能ではラベル検出以外にも不適切なコンテンツの検出機能も備えております。
こちらの機能だけ使いたい場合は「type: "ALL"」を「type: "UNSAFE"」としてください。
逆にラベル検出だけ行う場合は「type: "LABELS"」とします。

===　画像からエンティティを取得する
エンティティ(Entity)とは何でしょうか。Predictionsでは「顔や有名人」と定義されています。予測に使われているjsonを見るとわかりやすいです。

{ "entities": [ { "boundingBox": { "width": 0.3689453601837158, "height": 0.8123682737350464, "left": 0.3490826189517975, "top": 0.14206045866012573 }, "landmarks": [ { "type": "eyeLeft", "x": 0.49305182695388794, "y": 0.36409446597099304 }, { "type": "eyeRight", "x": 0.6503427624702454, "y": 0.40104830265045166 }, { "type": "mouthLeft", "x": 0.47494593262672424, "y": 0.6631938219070435 }, { "type": "mouthRight", "x": 0.6045310497283936, "y": 0.6924375295639038 }, { "type": "nose", "x": 0.5889276266098022, "y": 0.5378272533416748 } ], "attributes": {}, "metadata": { "confidence": 99.99987030029297, "pose": { "roll": 9.952530860900879, "yaw": 21.34749412536621, "pitch": -3.2121949195861816 } } } ] }
{ "entities": [ { "boundingBox": { "width": 0.5492957830429077, "height": 0.8666666746139526, "left": 0.26619717478752136, "top": 0.031111111864447594 }, "landmarks": [ { "type": "eyeLeft", "x": 0.4883432686328888, "y": 0.3638748824596405 }, { "type": "eyeRight", "x": 0.6443716883659363, "y": 0.41037192940711975 }, { "type": "nose", "x": 0.5983071327209473, "y": 0.5155085325241089 }, { "type": "mouthLeft", "x": 0.44799989461898804, "y": 0.6386198401451111 }, { "type": "mouthRight", "x": 0.601879894733429, "y": 0.6787497401237488 } ], "metadata": { "id": "vM6Pb1O", "name": "Hayao Miyazaki", "urls": [ "www.imdb.com/name/nm0594503" ], "pose": { "roll": 8.570178985595703, "yaw": 27.10132598876953, "pitch": 9.082789421081543 } } } ] }

 * boudingBox:顔全体の矩形
 * landmarks:顔のパーツ(目や鼻や口)
 * pose:顔の向き
 * confidence:信頼性？
 * name:一番似ている有名人の名前
 
有名人を検出する場合は「celebrityDetection: true」とするとjsonに出力されます。日本の有名人の検出も可能で精度が良いです。是非試してみてください。

== 日本語未対応のAIサービス
簡単にAI機能を開発できるPredictionsですがいくつか日本語に対応していないサービスもあります。これらの機能の詳細については、ブログにてご紹介します。

=== 音声認識
喋った内容からテキストを起こしてくれる機能がありますが、日本語の発音の認識は対応しておりません。

=== テキスト解析

テキストの内容から「言語」「感情」「構文」などを解析する機能がありますが、こちらは日本語に対応しておりません。

"1 validation error detected: Value 'ja' at 'languageCode' failed to satisfy constraint: Member must satisfy enum value set: [de, pt, en, it, fr, es]"

=== 画像からテキストを検出
次は画像からテキスト情報の抽出を行います。最初にお伝えした通り、OCR+αな情報を抜き出すことが可能です。しかし残念ながら日本語には対応しておりません。

//cmd{
$ amplify add predictions

? Please select from of the below mentioned categories 
> Identify

? Please select from of the below mentioned categories 
> Identify Text

$ amplify push
//}