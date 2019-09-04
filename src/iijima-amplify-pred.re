= どんとこい機械学習！AWS Amplify Predictionsでお手軽AI/ML開発

== はじめに
私は@<strong>{AWS Amplify}を業務で導入したりブログなどで紹介していますが、日々需要が高まってきていることを感じています。本章では2019年7月に追加された機能@<strong>{「Predictions」}を活用して簡単にAI/ML(人工知能と機械学習)サービスの開発をする方法をご紹介します。
@<br>{}

== AWS Amplifyについておさらい
AWS Amplifyはアプリケーションを素早く簡単に開発できるように「ストレージ/認証/解析/API」などの機能を提供しているAWSの各種マネージドサービス(Amazon S3/Amazon Cognitoなど)を、簡単に組み込める形で提供しているライブラリです。
@<br>{}
AWSが提供しているマネージドサービスサービスの面倒な設定をAWS Amplifyがまとめてやってくれる、とイメージしてください。

また似たような名称で@<strong>{AWS Amplify Console}というサービスがありますがこちらは「Gitリポジトリ等を活用した簡単に継続的ホスティングできるサービス」で、今回のものと少し違いますのでご注意ください。AWS AmplifyやAWS Amplify Consoleについてよくわからない。という方は、定期的に私のブログで紹介していますので、興味のある方はご覧ください。

== Predictionsの機能について
AWS Amplifyの新機能である@<strong>{Predictions}ですが、大きく以下のような機能を開発することが可能です。

==== Convert(変換)

  * 言語翻訳
  * 音声変換(テキスト→音声)
  * 音声認識(音声→テキスト)

==== Identify(識別)

  * 画像からラベル認識(現実世界の物体)
  * 画像からエンティティ認識(顔・有名人)
  * 画像から文字認識(単語・表・本のページ)
 
==== Interpret(解釈)
 
  * 自然言語処理

これらの機能については他のAWS Amplify機能と同様にAWSのAI/MLマネージドサービスを裏側で使用しています。

 * Amazon Translate(言語翻訳)
 * Amazon Polly(音声変換)
 * Amazon Transcribe(音声認識)
 * Amazon Rekognition(画像・動画分析)
 * Amazon Textract(OCR+構造化データ抽出)
 * Amazon Comprehend(自然言語処理)

AWS Amplifyでは簡単にアプリケーションを開発できますが、カスタマイズをしようと思うと裏側で使用しているマネージドサービスを調べたりすることが多くなるので、どのサービスを使っているのかを把握しておくことがオススメです。

== 環境構築
開発を行うにあたり環境構築を行います。AWS IAMでユーザーを作成する必要がありますので、「プログラムによるアクセス」ができる権限があるIAMユーザーを作成してください。以下のチュートリアルでは複数のAWSサービスを利用しますので、作成するユーザーについては管理者権限(AdministratorAccessのポリシーがアタッチされている状態)で作成されているのが望ましいです。

=== AWS Amplify CLIコマンドのインストール
AWS Amplifyを利用するのが初めての方は、AWS AmplifyのCLIコマンドを実行できるライブラリを追加します。

//cmd{
$ npm install -g @aws-amplify/cli
$ amplify configure
//}

=== Reactアプリケーション作成
今回はJavaScriptフレームワークのReact.jsを利用してWebアプリケーション開発を行いますので、必要なライブラリのインストールやひな形となるアプリケーションの作成を行います。

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

コマンドを実行して「開発エディタ」「開発アプリの種類」「フレームワークの種類」「パスの場所」「ビルドコマンド」を選択します。完了すると、AWS CloudFormationを通じてデプロイ用のS3のバケット・認証/未認証ユーザーのIAMロールが作成されます。
@<br>{}

最後にWebアプリケーションでAWS AmplifyのJavaScriptライブラリを使用するため、下記のインストールも行ってください。

//cmd{
$ yarn add aws-amplify
//}

== Predictionsを使用してAI/MLサービスの開発を行う
AWS Amplifyの初期設定が完了しましたので、Presictionsを使ってAI/ML開発を行ってみましょう。
@<br>{}

コマンドについてはできるだけ詳細に載せていますが、ソースコードは主要な部分のみ掲載しています。それぞれのサンプルコードはGitHubにアップロードしていますのでそちらを参考にしてください。GitHub等の各種URLは章末に記載しています。
@<br>{}

=== テキストから音声に変換
テキスト内容を音声に変換し再生する機能の開発を行なっていきます。この音声変換は@<strong>{Amazon Polly}が使われています。
@<br>{}

コマンドを実行してpredictionsを追加します。
//cmd{
$ amplify add predictions
//}

作成するAI/MLサービスの種類について設定を行なっていきます。

//cmd{
? Please select from of the below mentioned categories 
> Convert

# AWS Amplify Authが入ってない場合聞かれる可能性があります
? You need to add auth (Amazon Cognito) to your project in order to add storage for user files. 
  Do you want to add auth now? Yes

? What would you like to convert?
> Generate speech audio from text

? Provide a friendly name for your resourve
> (Enter)

? What is the source language?
> Japanese

? Select a speaker
> Mizuki

? Who should have access?
> Auth and Guest users
//}

完了したらpushを実行して、AWSのクラウド上に反映させます。

//cmd{
$ amplify push
//}

次はWebアプリケーションのプログラムを作成します。App.jsの先頭に以下のコードを追加します。

//listnum[init][Predictions機能の初期設定][js]{
import Amplify from '@aws-amplify/core';
import Predictions, { AmazonAIPredictionsProvider } from '@aws-amplify/predictions';
import awsconfig from './aws-exports';

Amplify.configure(awsconfig);
Amplify.addPluggable(new AmazonAIPredictionsProvider());
//}

上記はAI/MLサービス開発に必要な各種ライブラリなどのインポートとAmplifyの設定を行なっています。これより先に開発する全ての機能でこれらのライブラリを使用していきます。

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
テキストから音声に変換を行うプログラムです。textToGenerateSpeechは音声変換を行いたいテキストの変数です。上記の場合、引数のresultに音声変換されたデータ(audioStream)が入ってきますので、それを利用して音声の再生を行うことができます。

//listnum[audiostream][音声再生をおこなう][js]{
let AudioContext = window.AudioContext || window.webkitAudioContext;
const audioCtx = new AudioContext(); 
const source = audioCtx.createBufferSource();
audioCtx.decodeAudioData(result.audioStream, (buffer) => {
  source.buffer = buffer;
  source.connect(audioCtx.destination);
  source.start(0);
}, (err) => console.log({err}));
//}

#@# 使用する「声」についてはAWS Amplify CLIで作成時に選択した音声がデフォルト（今回の場合はMizuki）になりますが、voiceIdを変更することで別の声でも再生可能です。以下の例では男性のTakumiという声で再生を行います。

#@# //listnum[converttext2][voiceIdを指定して音声変換する][js]{
#@# textToSpeech: {
#@#   source: {
#@#     text: textToGenerateSpeech,
#@#   },
#@#   voiceId: "Takumi" //もしくは別の声 
#@# }
#@# //}

プログラムが完了したらローカル環境で確認するためにコマンドを実行します。

//cmd{
$ npm start
//}

テキストを入力すると簡単に音声がでませんでしたか？
@<br>{}

Amazon Pollyでは音声合成マークアップ言語(SSML)を利用することもできますが、現在AWS Amplifyで利用することはできません。

=== テキスト翻訳機能を追加する
次はテキストの翻訳を行います。この機能は@<strong>{Amazon Translate}を利用しています。AWS AmplifyのPredictionsでは@<strong>{AI/MLサービスを追加するごとにCLIコマンドの実行が必要}になります。

//cmd{
$ amplify add predictions

? Please select from of the below mentioned categories 
> Convert

? What would you like to convert?
> Translate text into a different language

? Provide a friendly name for your resourve
> (Enter)

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

「こんにちは」と入力すると、resultには {"text":"Hello","language":"en"} というオブジェクトが入ってきます。AWS Amplify CLIで作成した言語変換の情報がデフォルトですがそれ以外の言語変換を行いたい場合、@<strong>{targetLanguage}とsourceの中にある@<strong>{language}を変更するようにしてください。
@<br>{}

サポートしている言語情報については、下記のURLをご確認ください。
@<br>{}
@<href>{https://docs.aws.amazon.com/translate/latest/dg/how-it-works.html#how-it-works-language-codes}

====[column]React.jsの補足

setResponseという関数がありますが、これは「ステートフック」という機能です。関数コンポーネントにstateの機能を追加することができます。
@<br>{}
@<href>{https://ja.reactjs.org/docs/hooks-state.html}

====[/column]

=== テキスト翻訳と音声変換を組み合わせる
これまでで2つの「音声変換」「翻訳」の2つのAIサービスを作成しました。次はこれら2つのサービスを組み合わせて、読み上げを行う翻訳サービスを作ってみましょう。

 1. テキスト入力
 2. 英語に翻訳
 3. 翻訳した文章を音声で出力

先ほどまでの音声変換のプログラムでは声の設定が「Mizuki」という日本人女性の声になっていますので、英語の発音がよくありません。これを解決するためにvoiceIdの変更を行います。

//listnum[translatespeechtext][voiceIdを指定して音声変換をする][js]{
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
@<br>{}

@<href>{https://docs.aws.amazon.com/polly/latest/dg/voicelist.html}

=== 画像からラベル認識をおこなう
先ほどまでは翻訳や音声の変換を行いました。次は画像の識別(@<strong>{Identify})の実装を行なっていきます。
識別の1つ@<strong>{ラベル認識}は「与えられた画像に対してどこに何の物体があるかを識別しその名称と矩形範囲を出力する」機能です。

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

sourceに渡されているfileはFileオブジェクトの変数なので<input type="file" onChange="~">などで受け取って関数に渡すことが可能です。またこの機能ではラベル認識以外にも「@<strong>{安全ではないコンテンツ}」の検出機能も備えています。その機能だけ使いたい場合は「type: "ALL"」を「type: "UNSAFE"」としてください。逆にラベル検出だけ行う場合は「type: "LABELS"」とします。

実装が完了したら「npm start」を実行し、ローカル環境で画像をアップロードしてみましょう。表示されるJSONのパラメーターについては以下の表に掲載しました。
@<br>{}

//table[label1][ラベル検出で取得できるパラメーター]{
項目	概要          	備考
--------------------------------------
Name	物体の名前            	例:「Furniture」「Table」など
BoundingBox	画像上のラベルの位置            	Width/Height/Left/Topの数値で構成されます
Metadata	物体に関する情報            	下記のConfidence/Parentsが含まれます
Confidence	BoundingBoxの位置の精度            	-
Parents	物体の親ラベルの情報            	例:PCの場合Parentsに「Computer」と「Electronics」
Unsafe	アダルトコンテンツが含まれているか            	True/Falseで返却されます
//}

詳細に知りたい方はこちらのAmazon Rekognitionの公式ドキュメントをご確認ください。
@<br>{}
@<href>{https://docs.aws.amazon.com/AWSJavaScriptSDK/latest/AWS/Rekognition.html#detectLabels-property}

安全ではないコンテンツの検出の詳細についてはこちらの公式ドキュメントをご確認ください。
@<br>{}
@<href>{https://docs.aws.amazon.com/ja_jp/rekognition/latest/dg/moderation.html}

=== 画像からエンティティ認識をおこなう
エンティティ(Entity)とは何でしょうか。AWS AmplifyのPredictionsでは画像から取得できる顔や有名人の情報になります。呼び出す関数のパラメーターによって使える機能が変わりますのでご注意ください。
//cmd{
$ amplify add predictions

? Please select from of the below mentioned categories (Use arrow keys)
> Identify 

? What would you like to identify? 
> Identify Entities 

$ amplify push
//}

エンティティ認識を行うプログラムは以下のようになります。
//listnum[imageentity][画像からエンティティ認識をおこなう][js]{
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

celebrityDetectionをtrueにすると「有名人の認識」をおこないます。この場合、画像に複数の人間がいたとしてもその全員の顔の検出は行われず、@<strong>{有名人（と推測されたもの）の顔認識のみ行われます}。有名人については日本の有名人/芸能人の認識も可能で精度が良いです。是非試してみてください。

//table[entity1][エンティティ認識で取得できるパラメーター]{
項目	概要          	備考
--------------------------------------
BoundingBox	画像上の顔の位置            	Width/Height/Left/Topの数値で構成されます
Landmarks	顔のパーツ(目や鼻や口)            	typeとx,y座標で構成されます
Metadata	顔の詳細情報            	Pose/Nameなどで構成されます
Pose	顔の向き            	Roll/Pitch/Yawで構成されます
Name	推測された有名人の名前            	例:Jeff Bezos
//}

celebrityDetectionをfalse、あるいはパラメーターに追加しない場合は画像から検出された全部の顔の情報を出力します。出力されるJSONには@<strong>{Confidence}という情報が追加されます。こちらは画像のラベル認識と同様に「BoundingBoxの精度」になります。

== 独自の顔認証システムを構築する

上記のエンティティ認識では「顔の検出」あるいは「有名人の認識」が可能ですが、「独自に登録した人だけの顔の認識」を行うことも可能です。その実装に入る前に、この「独自の顔認識」機能はどういったユースケースが考えられるでしょうか。その1つに「顔認証受付サービス」にてAmazon Rekognitionを利用しているケースが紹介されています。
@<br>{}
@<href>{https://speakerdeck.com/hariby/dev-summit-2019}

こういった「顔認証サービス」を利用したサービスをPredictionsで開発することも可能です。

=== AWS Amplify Storageの追加
独自の顔認識システム構築する場合、認識させたい顔をAmazon S3にアップロード必要があるため、今回は手軽に画像アップロード環境を構築できる@<strong>{Storage}というAWS Amplifyの機能を追加します。Storageの概要については私のブログにてできるだけ詳細に説明をしていますので、そちらをご覧ください。@<href>{https://omuriceman.hatenablog.com/entry/amplify1}

この記事では、Storageを作成しアプリケーションに追加する流れを簡単におさらいします。以下のコマンドを実行してください。

//cmd{
$ amplify add storage
? Please select from one of the below mentioned services
> Content (Images, audio, video, etc.) 

? Please provide a friendly name for your resource that will be used to 
label this category in the project:(そのままEnter)

? Please provide bucket name:(そのままEnter)

? Who should have access:
>Auth and guest users 

? What kind of access do you want for Authenticated users?
>◉ create/update
 ◉ read
 ◉ delete

#上記は認証済みユーザーはファイル操作のcreate/update,read,delete全てをすることが可能になります。キーボードでaを押すと全選択できます。

? What kind of access do you want for Guest users? 
>◉ create/update
 ◉ read
 ◯ delete

#今回のアプリケーションではログイン認証機構を作成していないので、未認証のユーザーもcreate/updateをできる必要があります。個別に権限を選択する場合はスペースキーを押してください。

? Do you want to add a Lambda Trigger for your S3 Bucket? (そのままEnter)

//}
ここまででStorageの初期設定ができました。念の為Storage機能が追加されているか確認しましょう。

//cmd{
$ amplify status
//}

//table[amplifystatus][amplify status実行例]{
Category	Resource Name          	Operation  	Provider Plugin
--------------------------------------
Storage	s3...            	Create 	awscloudformation
//}

となっていれば作成は完了です。ローカル環境で作成されたStorageの設定をpushしてAWSクラウド上に反映しましょう。

//cmd{
$ amplify push
//}

AWS CloudFormationが実行されて、設定したS3環境が構築されますので完了するまで数分待ちます。
@<br>{}

完了するとaws-exports.jsファイルにS3関連の設定情報が追記されています。

 * aws_user_files_s3_bucket
 * aws_user_files_s3_bucket_region
 
=== AWS Amplify Predictionsを再設定する
すでに上記で一度エンティティ認識を試している場合、Predictionsのアップデートが必要になります。

//cmd{
$ amplify update predictions
? Please select from of the below mentioned categories (Use arrow keys)
> Identify 

? Which identify resource would you like to update?
> identifyEntities...

? Would you like use the default configuration? 
> Advanced Configuration 

? Would you like to enable celebrity detection? Yes

? Would you like to identify entities from a collection of images? Yes

? How many entities would you like to identify? 10

? Would you like to allow users to add images to this collection? Yes

? Who should have access? 
> Auth and Guest users 

//}

amplify statusの状態は以下の通りです。

//table[amplifystatus2][amplify status]{
Category	Resource Name          	Operation  	Provider Plugin
--------------------------------------
Function	RekognitionIndexFacesTrigger...            	Create 	awscloudformation
Predictions	identifyEntities...            	Update 	awscloudformation
Storage	s3...            	Update 	awscloudformation
//}

ここで新たに@<strong>{Function}というカテゴリーが追加されています。これはAWS Lambdaで動くプログラムになっており、ファイルは./amplify/backend/function/{Resource Name}/に生成されています。
@<br>{}

amplify pushを行うとこれらのローカルファイルがAWS CloudFormationによってデプロイされて、AWS Lambdaに反映されます。

=== アップロードした顔画像をインデックス付けする
Storage/Function/Predictionsという３つの要素で独自の顔認証が構築されるのですが、先ほどまではコマンドを実行していただけですのでフローが理解しづらいと思います。理解の補足のために図を作成しました。

//image[upload_face][顔の画像が登録される流れ][scale=0.8]

図中の3番についてはAWS Lambdaにアップロードされたソースコード(./amplify/backend/function/{Resource Name}/src/index.js)に画像をコレクションに登録する関数があります。

//listnum[rekognition][コレクションに顔を追加する][js]{
const params1 = {
  CollectionId: process.env.collectionId,
  ExternalImageId: externalImageId,
  Image: {
    S3Object: {
      Bucket: bucketName,
      Name: decodeKey,
    },
  },
};

const result = await rekognition.indexFaces(params1).promise(); // <-ここが重要
//}

AWS Amplify CLIコマンドを実行したことで、図中の2~4までのバックエンド処理は構築が完成していますので次はStorageを使った画像のアップロードを行っていきます。

=== Storageを使用して画像をアップロードする
AWS Amplify Storageを利用した画像のアップロード方法についてまずはStorageに関する主要コードを掲載します。まずはStorageのimportを行います。

//listnum[importstorage][Storageをインポートする][js]{
import React, { useState } from 'react';
import './App.css';
import Amplify, { Predictions,Storage } from 'aws-amplify'; // <- ここにStorageを追加しています
import { AmazonAIPredictionsProvider } from '@aws-amplify/predictions';
//}

次にアップロードです。
//listnum[storage][画像をアップロードするコード][js]{
    Storage.put(file.name, file, {
      level: 'protected',
      customPrefix: {
        protected: 'protected/predictions/index-faces/',
      }
    });
//}

Storage機能によるファイルのアップロード機能では、protectedやprivateの権限でアップロードを行うとユーザーごとに割り振られたuser_identity_id(Amazon Cognito Identity ID)がバケット名が先頭についてしまいます。
//listnum[storagepath1][一般的なStorageのアップロードパス]{
protected/{user_identity_id}/hoge.png
//}

customPrefixを指定することで、user_identity_idの手前に指定した名前のパスを指定することが可能です。
//listnum[storagepath2][customPrefixを付けた場合のアップロードパス]{
protected/predictions/index-faces/{user_identity_id}/hoge.png
//}

このようにすることで前の項で説明したS3へ画像のアップロードを検知してLambdaを発動させる対象のバケット範囲を絞ることができるようになるのです。上記の場合はindex-facesにアップロードされた画像のみLambdaをキックさせることができます。
@<br>{}

ここまで完了したら、独自画像の顔認識を検証するために自分を含めた数枚程度の顔画像をアップロードするようにしてください。

=== Predictionsを使用して顔認証をおこなう
最後に顔の認識をおこないます。先ほどまでの作業で、任意の顔画像をアップロードしてインデックス登録されるところまで完了しました。次に登録されている顔と同じ顔の画像をアップして正しく認識できるか確認を行いましょう。
@<br>{}

先ほどのエンティティ検出のコードを1行変更するだけで対応ができます。
//listnum[imageentity2][画像から独自の顔認証を行う][js]{
Predictions.identify({
  entities: {
    source: {
      file,
    },
    collection:true,
  }
}).then(result => {
  setResponse(JSON.stringify(result, null, 2));
})
  .catch(err => console.log(err))
//}

resultには前述したエンティティ検出のパラメーター以外に2つ追加されています。

 * externalImageId アップロードされた画像と似ている画像のパス
 * similarity externalImageIdとの類似度

ほんのわずかな時間で独自の顔認識システムが完成してしまいました。AWS Amplify Predictionsおそるべしですね。

== 日本語未対応のAIサービス
簡単にAI機能を開発できる@<strong>{Predictions}ですがいくつか日本語に対応していない機能もあります。これらの詳細については、私個人の技術ブログにてご紹介します。

=== 音声認識
Convertの機能の1つで「喋った内容からテキストを起こしてくれる」機能がありますが、日本語の発音の認識は対応しておりません。Alexaで日本語の認識はできているので追加されることを期待しています。@<strong>{Amazon Transcribe}を利用しています。

=== テキスト解析
Interpretの機能で、テキストの内容から「言語」「感情」「構文」などを解析する機能がありますが、こちらは日本語に対応しておりません。@<strong>{Amazon Comprehend}を利用しています。

#@# "1 validation error detected: Value 'ja' at 'languageCode' failed to satisfy constraint: Member must satisfy enum value set: [de, pt, en, it, fr, es]"

=== 画像からテキストを検出
Identifyの機能で、画像からテキスト情報の抽出を行います。OCR+構造化データなどの情報を抜き出すことが可能でとても便利な機能です。しかし残念ながら日本語には対応しておりません。@<strong>{Amazon Rekognition/Amazon Textract}を利用しています。

//embed[latex]{
\clearpage
//}

== まとめ
この章ではAWS Amplifyに追加された「Predictions」を利用したAI/MLサービスについてご紹介しました。CLIコマンドの実行と数行のプログラムでアプリケーションの簡単に実装できるようになっていて、AI/MLサービスが身近になっていることを実感します。

==== AWS Amplifyを学習する上で押さえておくべきポイント
最初にお伝えした通りAWS Amplifyは裏側で他のAWSマネージドサービスを利用しています。AWS Amplifyの公式サイトの情報では理解ができない場合、下記のドキュメントなどを見ると理解が深まるかもしれません。

 * AWS AmplifyのGitHub
 * AWS JavaScriptSDKのドキュメント
 * 裏側で使われているマネージドサービスのドキュメント
 
を見るとより理解が深まります。例えば今回のAI/MLサービスでは、AWS Amplifyの公式ドキュメント上ではどのようなJSONのレスポンスになっているかが記載されておりませんでしたが、GitHubの情報から使用されている関数を特定してJavaScriptSDKのドキュメントを調査。それと同時にマネージドサービスのドキュメントの調査も行うようにして仕様の把握をおこなっています。
@<br>{}

== Appendix

 * AWS Amplifyの公式ドキュメント 
 @<br>{}
 @<href>{https://aws-amplify.github.io/docs/js/predictions}
 * AWS AmplifyのPredictionsのGitHubにあるJavaScriptライブラリ 
 @<br>{}
 @<href>{https://github.com/aws-amplify/amplify-js/tree/master/packages/predictions}
 * 本章にて作成したサンプルプログラム 
 @<br>{}
 @<href>{https://github.com/wataruiijima/amplify-predictions}
 * AWS Amplify情報などを発信している個人の技術ブログ 
 @<br>{}
 @<href>{https://omuriceman.hatenablog.com}
