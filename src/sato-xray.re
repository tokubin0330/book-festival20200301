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

トレースデータを送信する方法は３種類あります。これから、それぞれの方法で実際にX-Rayにトレースデータを送信してみます。

今回はローカルにDockerコンテナでテスト用の実行環境を作るため、DockerとDocker Composeが必要になります。
インストール方法は以下の各公式サイトを参考にしてください。

 * Dockerのインストール@<br>{}@<href>{https://docs.docker.com/install/}
 * Docker Composeのインストール@<br>{}@<href>{https://docs.docker.com/compose/install/}

インストールが完了したら各コマンドを叩いて、正常にインストールがされていことを確認しましょう。筆者の環境では下記のような表示になりました。

//cmd{
$ docker --version
Docker version 19.03.1, build 74b1e89

$ docker-compose --version
docker-compose version 1.24.1, build 4667896b
//}

X-Rayへアプリケーション側からデータを送信するにはX-Rayへの書き込み権限が必要になりますので、
必要なIAMポリシーをもったユーザーを作成します。
ACCESS_KEYとSECRET_IDは環境に認証情報を設定する際に使用しますので、どこかにコピーしておきます。

// IAMユーザー作成〜認証情報作成の画面を３〜５枚程度挿入 //

=== X-Ray SDKとX-Rayデーモンを利用する

デーモンの配置が必要ですが、SDKが対応している言語、環境であれば比較的かんたんに始められる方法です。
なお、AWS Lambdaで利用する場合は、デーモンをユーザー側で配置する必要はありません。

X-Ray SDKの対応言語

 * Java
 * Go
 * Node.js
 * Python
 * Ruby
 * .NET


//quote{
Node.jsのX-Ray SDKでトレースデータの収集を行いましたが、
SQLクエリがキャプチャができず、
執筆期間内で原因を調査していましたが原因の特定が間に合わなかったため
サンプルプログラムでは手動で収集を行いました。
//}


ここでは、Node.jsを利用して送信してみます。
SDKは各ライブラリをラッピングしてトレースデータを収集するため、
受信リクエストはExpressまたはRestify、SQLクエリはpgまたはmysqlを利用ししているものが収集対象です。
各言語の対応環境の詳細については、X-Rayの開発者ガイドなどを参照してください。

 * @<href>{https://docs.aws.amazon.com/ja_jp/xray/latest/devguide/aws-xray.html}


サンプルコードは下記GitHubリポジトリに保存しています。

 * @<href>{https://github.com/takaaki-s/xray-node-example}

今回は下記のようにコンテナを定義しました。

//list[nodejs-dockercompose][docker-compose.yml]{
version: '3.7'
services:
  nodejs:
    image: node:12-alpine
    init: true
    working_dir: /home/node/app
    volumes:
      - ./app:/home/node/app
      - ./.aws:/root/.aws
    ports:
      - '3000:3000'
    command: /bin/sh -c "npm install && npm run dev"
  db:
    image: mariadb:10.4-bionic
    ports:
      - "3306:3306"
    environment:
      MYSQL_ROOT_PASSWORD: password
      MYSQL_DATABASE: xray_example
    volumes:
      - ./db-data:/var/lib/mysql
  xrayd:
    build: ./docker/xrayd
    volumes:
      - ./.aws:/root/.aws
    expose:
      - "2000"
    environment:
      - AWS_REGION=ap-northeast-1
  awscli:
    build: ./docker/awscli
    volumes:
      - ./.aws:/root/.aws
//}


はじめに、AWSの認証情報をこのテスト用の環境に設定します。
下記コマンドを実行して、先ほど作成したユーザーのアクセスキーとシークレットアクセスキーを設定してください。
なお、今回は東京リージョン（ap-northeast-1）を指定してください。

//cmd{
$ docker-compose run --rm awscli aws configure

AWS Access Key ID [None]: <あなたのアクセスキー>
AWS Secret Access Key [None] <あなたのシークレットアクセスキー>
Default region name [None]: ap-northeast-1
Default output format [None]: 何も入力せずにENTER
//}

環境の構築ができたので、テスト用の環境を起動します。

//cmd{
$ docker-compose up -d
$ docker-compose exec nodejs npx knex migrate:latest
$ docker-compose exec nodejs npx knex seed:run
//}





=== AWS SDKを利用する

=== AWS CLIを利用する

== 収集したデータの可視化と分析

== その他の使いかた

