= AWS Amplify Predictionsで始めるAI/ML入門

== はじめに
私は@<strong>{AWS Amplify}を業務での導入やブログなどで紹介しておりますが、日々需要が高まってきていることを感じています。この章では2019年7月に追加された機能@<strong>{「Predictions」}を活用したAI/MLサービスの開発をご紹介したいと思います。

== AWS Amplifyについておさらい
AWS AmplifyはWebアプリケーションを素早く簡単に開発できるように「ストレージ/認証/解析」などの機能を提供しているAWSの各種マネージドサービスを、CLIコマンドを実行するだけで簡単に組み込める形で提供しているライブラリです。
AWSが提供している各種サービス(Amazon S3/Amazon Cognitoなど)を簡単に扱う手段をAWS Amplifyが提供している、とイメージしてください。

また似たような名称で@<strong>{AWS Amplify Console}というサービスがありますがこちらは「Gitリポジトリ等を活用した簡単に継続的ホスティングできるサービス」で、今回のものと若干違いますのでご注意ください。AWS AmplifyやAWS Amplify Consoleについてよくわからない。という方は、定期的に私のブログで紹介しておりますので、詳しく知りたい方はご覧ください。

== Predictionsの機能について
AWS Amplifyの新機能である@<strong>{Predictions}ですが、大きく以下のような機能を開発することが可能です。

 1. Convert(変換)

  * 言語翻訳
  * 音声変換
  * 音声認識

 2. Identify(識別)

  * 画像から文字認識(単語・表・本のページ)
  * 画像からエンティティ認識(顔・有名人)
  * 画像からラベル認識(現実世界の物体)
 
 3. Interpret(解釈)
 
  * 自然言語処理

これらの機能も他のAWS Amplifyの機能と同様にAWSのAIサービスを裏側で使用しています。

 * Amazon Translate(言語翻訳)
 * Amazon Polly(音声変換)
 * Amazon Transcribe(音声認識)
 * Amazon Rekognition(画像・動画分析)
 * Amazon Textract(OCR+構造化データ抽出)
 * Amazon Comprehend(自然言語処理)

AWS Amplifyでは簡単にアプリケーションを開発できますが、カスタマイズをしようと思うと裏側で使用しているサービスを調べたりすることが多くなるので、どのサービスを使っているのかを把握しておくことを心がけるようにしてください。

== 環境構築
開発を行うにあたり環境構築を行います。事前にAWS IAMでユーザーを作成する必要があり、「プログラムによるアクセス」ができる権限があるIAMユーザーを作成してください。以下のチュートリアルでは複数のAWSサービスを利用しますので、作成するユーザーについては管理者権限で作成されているのが望ましいです。

=== AWS Amplify CLIコマンドのインストール
AWS Amplifyを利用するのが初めての方は、AWS AmplifyによるCLIコマンドを実行できるライブラリを追加します。

//cmd{
$ npm install -g @aws-amplify/cli
$ amplify configure
//}

=== Reactアプリ作成
今回はJavaScriptのフレームワークのReactを利用してWebアプリ開発を行いますので、必要なコマンドを実行します。

//cmd{
$ npm install -g create-react-app
$ create-react-app myapp && cd myapp
$ npm start
//}

=== AWS Amplifyの初期設定
次にAWS AmplifyのCLIコマンドで初期設定を行います。

//cmd{
$ amplify init
//}

コマンドを実行して「開発エディタ」「開発アプリの種類」「フレームワークの種類」「パスの場所」「ビルドコマンド」を選択します。完了すると、AWS CloudFormationがデプロイ用のS3のバケット・認証/未認証ユーザーのIAMロールが行われます。最後にWebアプリでAWS AmplifyのJavaScriptライブラリを使用するため、下記のインストールも行ってください。

//cmd{
$ yarn add aws-amplify
//}

== AIサービスの開発を行う
Presictionsの機能を使って開発を行ってみましょう。それぞれのサンプルコードはGitHubにアップロードしておきます。GitHub等の各種URLは巻末に記載してあります。

=== テキストから音声に変換
テキスト内容を音声に変換し再生する機能の開発を行なっていきます。この音声変換は@<strong>{Amazon Polly}が使われております。

//cmd{
$ amplify add predictions
//}

コマンドを実行すると作成するAI/MLサービスの種類についての対話式に設定を行なっていきます。

//cmd{
? Please select from of the below mentioned categories 
> Convert

? What would you like to convert?
> Generate speech audio from text

? Provide a friendly name for your resourve
> (表示された文字列のままEnterで進めてください)

? What is the source language?
> Japanese

? Select a speaker
> Mizuki

? Who should have access?
> Auth and Guest users
//}

完了したらCLI上でpushしましょう。

//cmd{
$ amplify push
//}

次はプログラムを行います。
App.jsに以下のようなコードを追加します

//listnum[init][Predictions機能の初期設定][js]{
import Amplify from '@aws-amplify/core';
import Predictions, { AmazonAIPredictionsProvider } from '@aws-amplify/predictions';
import awsconfig from './aws-exports';

Amplify.configure(awsconfig);
Amplify.addPluggable(new AmazonAIPredictionsProvider());
//}

App.jsのファイルの先頭に各種必要なライブラリなどのインポートとAmplifyの設定を行なっています。

//listnum[converttext][テキストから音声に変換する][js]{
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
テキストから音声に変換を行うプログラムです。textToGenerateSpeechは変数でinput要素に入力されたテキストを関数に渡しています。上記の場合resultに音声変換されたデータ(audioStream)が入ってきますので、audioStreamを利用して音声の再生を行うことができます。音声再生のコード部分についてはGitHubのコードをご参照ください。

//listnum[converttext2][VoiceIdを指定して音声変換する][js]{
      textToSpeech: {
        source: {
          text: textToGenerateSpeech,
        },
        voiceId: "Takumi" //もしくは別の声 
      }
//}
使用する「声」についてはCLIで作成時に選択した音声がデフォルト（今回の場合はMizuki）になりますが、voiceIdを変更することで別の声でも再生可能です。上記の例では男性のTakumiという声で再生を行います。

プログラムが完了したらローカル確認するためにコマンドを実行します。

//cmd{
$ npm start
//}

簡単に音声がでませんでしたか？ 
@<br>{}

Amazon Pollyでは音声合成マークアップ言語(SSML)を利用することもできますが、現在AWS Amplifyで利用することはできません。SSMLを利用したい場合はAWS AmplifyのソースコードについてはGitHubに公開されているので、そちらを参考に独自にプログラムを行うのがいいかもしれません。

=== テキスト翻訳機能を追加する
次はテキストの翻訳を行います。この機能は@<strong>{Amazon Translate}を利用しています。AWS AmplifyのPredictionsではAIサービスを追加するごとにCLIコマンドの実行が必要になります。

//cmd{
$ amplify add predictions

? Please select from of the below mentioned categories 
> Convert

? What would you like to convert?
> Translate text into a different language

? Provide a friendly name for your resourve
> (表示された文字列のままEnterで進めてください)

#以下は日本語から英語に変換する場合の例です
? What is the source language?
> Japanese

? What is the target language?
> English

? Who should have access?
> Auth and Guest users

$ amplify push
//}

次はプログラムを追加します。
//listnum[translatettext][テキストを翻訳する][js]{
    Predictions.convert({
      translateText: {
        source: {
          text: textToTranslate,
          // language : "es" // defaults configured on aws-exports.js
        },
        // targetLanguage: "en"
      }
    }).then(result => setResponse(JSON.stringify(result, null, 2)))
      .catch(err => setResponse(JSON.stringify(err, null, 2)))
//}

input要素に「こんにちは」と入力すると、resultには {"text":"Hello","language":"en"} という形式のオブジェクトが入ってきます。CLIで作成した言語変換の情報がデフォルトですがそれ以外の言語変換を行いたい場合、@<strong>{targetLanguage}とsourceの中にある@<strong>{language}を変更するようにしてください。

サポートしている言語情報については@<href>{https://docs.aws.amazon.com/translate/latest/dg/how-it-works.html#how-it-works-language-codes}をご参照ください。

====[column]React.jsの補足

setResponseという関数がありますが、これは「ステートフック」という機能です。関数コンポーネントにstateの機能を追加することができます。

====[/column]

=== テキスト翻訳と音声変換を組み合わせる
これまでの章で2つの「音声変換」「翻訳」の2つのAIサービスを作成しました。次はこれら2つのサービスを組み合わせて、読み上げを行う翻訳サービスを作ってみましょう。

 1. テキスト入力
 2. 英語に翻訳
 3. 翻訳した文章を音声で出力

まず先ほどまでの音声変換のプログラムでは声の設定が「Mizuki」という日本人女性の声になっていますので、英語の発音がよくありません。これを解決するために@<strong>{voiceId}の変更を行います。

//listnum[translatespeechtext][VoiceIdを指定して音声変換をする][js]{

  function generateTextToSpeech(text) {
    Predictions.convert({
      textToSpeech: {
        source: {
          text: text,
        },
        voiceId: "Amy", //CLIで設定したvoiceIdを変更したい場合はこのように指定します 
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

次に上記の関数（上記の場合はgenerateTextToSpeech）を翻訳結果のプログラムから呼び出せば完成です。
//listnum[translatetranslate][翻訳をおこなって音声変換の関数を呼び出す][js]{
  function translate() {
    Predictions.convert({
      translateText: {
        source: {
          text: textToTranslate,
        },
      }
    }).then(result => {
      generateTextToSpeech(result.text)
    })
      .catch(err => setResponse(JSON.stringify(err, null, 2)))
  }
//}

二つのコードを組み合わせるだけで新しいAI機能を開発できるのでとても便利ですね。声の一覧はこちらからご覧になれます。

@<href>{https://docs.aws.amazon.com/polly/latest/dg/voicelist.html}

=== 画像からラベル付けをおこなう
先ほどまでは翻訳や音声の変換を行いました。次は画像の識別(@<strong>{Identify})の実装を行なっていきます。
識別の1つ@<strong>{ラベル付け}は「与えられた画像に対してどこに何の物体があるかを識別しその名称と矩形範囲情報を出力する」機能です。

早速試してみましょう。AWS Amplify CLIコマンドを実行します。(以降の対話入力については重要な箇所のみ記載いたします。)

//cmd{
$ amplify add predictions

? Please select from of the below mentioned categories 
> Identify

? Please select from of the below mentioned categories 
> Identify Labels

$ amplify push
//}

プログラムは下記のコードを呼び出すことでラベル情報を取得することができます。

//listnum[imagelabeling][画像からラベル情報を取得する][js]{
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

sourceに渡されているfileはFileオブジェクトですので<input type="file" onChange="~">などで受け取って関数に渡すことが可能です。この機能ではラベル検出以外にも@<strong>{安全ではないコンテンツ}の検出機能も備えております。こちらの機能だけ使いたい場合は「type: "ALL"」を「type: "UNSAFE"」としてください。逆にラベル検出だけ行う場合は「type: "LABELS"」とします。実装が完了したら「npm start」を実行し、ローカル環境で画像をアップロードしてみましょう。表示されるJSON情報の内容について補足します。

 * Name - 物体の名前(例:「Furniture」「Table」など)
 * BoundingBox - 画像上のラベルの位置。Width/Height/Left/Topの数値で構成されます
 * Metadata - 物体に関する情報です。下記のConfidence/Parentsが含まれます。
 * Confidence - BoundingBoxの位置の精度
 * Parents - 物体の親ラベルの情報が含まれることがあります。複数存在する場合もあります(例:PCの場合ParentsにComputerとElectronics)。
 * Unsafe - True/False。画像内にアダルトコンテンツが1つ以上存在する場合、Trueが返却されます。

詳細に知りたい方はこちらのAmazon Rekognitionの公式ドキュメントをご確認ください。
@<br>{}
@<href>{https://docs.aws.amazon.com/AWSJavaScriptSDK/latest/AWS/Rekognition.html#detectLabels-property}

安全ではないコンテンツの検出の詳細についてはこちらの公式ドキュメントをご確認ください。
@<br>{}
@<href>{https://docs.aws.amazon.com/ja_jp/rekognition/latest/dg/moderation.html}

===　画像からエンティティを取得する
エンティティ(Entity)とは何でしょうか。AWS AmplifyのPredictionsでは画像から取得できる顔や有名人の情報です。呼び出す関数のパラメーターによって使える機能が変わります。

//listnum[imageentity][画像からエンティティ情報を取得する][js]{
    Predictions.identify({
      entities: {
        source: {
          file,
        },
        celebrityDetection: true, 
      }
    }).then(result => {
      setResponse(JSON.stringify(result, null, 2));
    })
      .catch(err => console.log(err))
//}

celebrityDetectionをtrueにすると「有名人の検出」をおこないます。この場合、画像に複数の人間がいたとしてもその全員の顔の検出を行われず、有名人（と推測されたもの）の顔検出のみ行われます。

 * BoundingBox - 画像上の顔の位置。Width/Height/Left/Topの数値で構成されます
 * Landmarks - 顔のパーツ(目や鼻や口)。typeとx,y座標で構成されます
 * Metadata - 顔の詳細情報。Pose/Nameなどで構成されます
 * Pose - 顔の向き。Roll/Pitch/Yawで構成されます
 * Name - 推測された有名人の名前(例:Jeff Bezos)

celebrityDetectionをfalse、あるいはパラメーターに追加しない場合は検出された全員の顔の情報を出力します。出力では@<strong>{Confidence}という情報が追加されます。こちらは画像のラベリングと同様に「BoundingBoxの精度」になります。有名人検出機能については日本の有名人の検出も可能で精度が良いです。是非試してみてください。

=== 独自の顔マッチングシステムを構築する


== 日本語未対応のAIサービス
簡単にAI機能を開発できる@<strong>{Predictions}ですがいくつか日本語に対応していない機能もあります。これらの詳細については、私個人の技術ブログにてご紹介します。

=== 音声認識
Convertの機能の1つに喋った内容からテキストを起こしてくれる機能がありますが、日本語の発音の認識は対応しておりません。Alexaで日本語の認識はできているので追加されることを期待しています。@<strong>{Amazon Transcribe}を利用しています。

=== テキスト解析
Interpretの機能で、テキストの内容から「言語」「感情」「構文」などを解析する機能がありますが、こちらは日本語に対応しておりません。@<strong>{Amazon Comprehend}を利用しています。

"1 validation error detected: Value 'ja' at 'languageCode' failed to satisfy constraint: Member must satisfy enum value set: [de, pt, en, it, fr, es]"

=== 画像からテキストを検出
Identifyの機能で、画像からテキスト情報の抽出を行います。OCR+構造化データなどの情報を抜き出すことが可能でとても便利な機能です。しかし残念ながら日本語には対応しておりません。@<strong>{Amazon Rekognition/Amazon Textract}を利用しています。

== まとめ
この章ではAWS Amplifyに追加された「Predictions」を利用したAI/MLサービスについてご紹介しました。CLIコマンドの実行と数行のプログラムでアプリケーションの簡単に実装できるようになっていて、AI/MLサービスが身近になっていることを実感します。

=== AWS Amplifyを学習する上で押さえておくべきポイント
最初にお伝えした通りAWS Amplifyは裏側で他のAWSマネージドサービスを利用しています。AWS Amplifyの公式サイトの情報では理解ができない場合、下記のドキュメントなどを見ると理解が深まるかもしれません。

 * AWS AmplifyのGitHub
 * AWS JavaScriptSDKのドキュメント
 * 裏側で使われているマネージドサービスのドキュメント
 
を見るとより理解が深まります。例えば今回のAI/MLサービスでは、AWS Amplifyの公式ドキュメント上ではどのようなJSONフォーマットになっているかが記載されておりませんでしたが、GitHubの情報から使用されている関数を特定してJavaScriptSDKのドキュメントを調査。それと同時にマネージドサービスのドキュメントの調査も行うようにして仕様の把握をおこなっています。

== 関連URLについて

 * 本章にて作成されたソースコード @<href>{https://github.com/}
 * AWS Amplifyの公式ドキュメント @<href>{https://aws-amplify.github.io/docs/js/predictions}
 * AWS AmplifyのPredictionsのGitHubにあるJavaScriptライブラリ @<href>{https://github.com/aws-amplify/amplify-js/tree/master/packages/predictions}
 * AWS Amplify情報を発信している個人の技術ブログ @<href>{https://omuriceman.hatenablog.com}
