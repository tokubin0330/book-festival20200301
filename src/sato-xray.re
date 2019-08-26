= AWS X-Rayで始めるパフォーマンス監視入門

== パフォーマンス監視について

みなさんはアプリケーションのパフォーマンス監視を行っていますか？

「ある特定の操作のときだけレスポンスが悪い」という状態は、
外形監視やメトリクスの監視だけでは気付くことが困難ですし、
監視ログからそれを探し出すにしても、しっかりとしたログ設計と分析体制を整えていなければ対応できません。
そして気付けないままある日、ユーザーからの問い合わせで発覚するという経験している方もいるのではないでしょうか。

そこで、転ばぬ先の杖ということでアプリケーション内部のパフォーマンス監視を行うためのマネージドサービスである AWS X-Ray をご紹介したいと思います。

== X-Rayとは

アプリケーションが処理するリクエストやレスポンスに関するデータを収集し可視化、分析するためのサービスです。
分散トレーシングに対応しているため複雑化したマイクロサービスであってもリクエストを追跡が可能で、
X-Ray SDKが対応している開発言語（環境）であれば、コードにはほぼ手を入れずにすぐに利用できます。

== X-Rayの画面

サービスマップ

// サービスマップの画面を貼る //

トレース

// トレース画面を貼る //

トレース詳細

// トレース詳細の画面を貼る //

== X-Rayへトレースデータを送信する

トレースデータを送信する方法は３種類あります。それぞれの方法を試していきます。

=== １．X-Ray SDKとX-Rayデーモンを利用する

デーモンの配置が必要ですが、SDKが対応している言語、環境であれば一番かんたんに始められる方法です。
なお、AWS Lambdaで利用する場合は、デーモンをユーザー側で配置する必要はありません。

X-Ray SDKの対応言語

 * Java
 * Go
 * Node.js
 * Python
 * Ruby
 * .NET

今回は、Node.jsを利用して送信してみましょう。
SDKは各ライブラリをラッピングしてトレースデータを収集するため、
受信リクエストはExpressまたはRestify、SQLクエリはpgまたはmysqlを利用ししているものが収集対象です。


=== ２．AWS SDKを利用する

=== ３．AWS CLIを利用する

今回はローカルにテスト用の実行環境を作るため、
@<ami>{AWS CLI}、@<ami>{Docker}、@<ami>{Docker Compose}が必要になります。
インストール方法は以下の各公式サイトを参考にしてください。

 * AWS CLIのインストール@<br>{}@<href>{https://docs.aws.amazon.com/ja_jp/cli/latest/userguide/cli-chap-install.html}
 * Dockerのインストール@<br>{}@<href>{https://docs.docker.com/install/}
 * Docker Composeのインストール@<br>{}@<href>{https://docs.docker.com/compose/install/}

インストールが完了したら各コマンドを叩いて、正常にインストールがされていことを確認しましょう。筆者の環境では下記のような表示になりました。

//cmd{
$ aws --version
aws-cli/1.16.166 Python/3.7.3 Darwin/18.7.0 botocore/1.12.156

$ docker --version
Docker version 19.03.1, build 74b1e89

$ docker-compose --version
docker-compose version 1.24.1, build 4667896b
//}

X-Rayへアプリケーション側からデータを送信するにはX-Rayへの書き込み権限が必要になりますので、
必要なIAMポリシーをもったユーザーを作成します。

// IAMユーザー作成〜認証情報作成の画面を３〜５枚程度挿入 //

次に、認証情報をローカルに設定します。

//cmd{
$ aws configure --profile xray-test
//}

ここからテスト用のアプリケーションを構築していきます。
適当なディレクトリを作成して、そのなかにプロジェクト用のファイルを作成していきます。

//list[xray-packagejson][package.json]{
{
  "name": "xray-node-example",
  "version": "0.0.0",
  "private": true,
  "scripts": {
    "start": "node app.js"
  }
}
//}

次に、必要なパッケージをインストールします。

//cmd{
$ npm install express aws-sdk aws-xray-sdk
//}

X-Rayをテストするプログラムを設置します。

//list[xray-appjs][app.js]{
const express = require('express');
const app = express();

app.get('/', (req, res) => {
  res.send('Hello World');
});

console.log('hoge');
app.listen(3000);
//}

設置したプログラムを実行するDockerコンテナの定義ファイルを書きます。

//list[xray-dockerjson][docker-compose.yml]{
version: '3.7'
services:
  nodejs:
    image: node:12-alpine
    init: true
    working_dir: /home/node/app
    volumes:
      - ./app:/home/node/app
    ports:
      - '3000:3000'
    command: /bin/sh -c "npm install && npm run dev"
//}

コンテナを起動してプログラムを実行してみましょう。

//cmd{
$ docker-compose up
//}

コンテナが起動したあとにlocalhost:3000にアクセスするとHello Worldと表示されると思います。
このときすでにX-Rayに計測されたデータが送信されているはずですので、画面を確認してみましょう。


//list[aa][ほげ]{
aaaa
//}

== 収集したデータの可視化と分析

== その他の使いかた

