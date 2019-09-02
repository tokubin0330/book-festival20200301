= まるっとお見通し！AWS X-Rayでパフォーマンス監視

== パフォーマンス監視について

みなさんはアプリケーションのパフォーマンス監視を行っていますか？

「ある特定の操作のときだけレスポンスが悪い」という状態は、
外形監視やメトリクスの監視だけでは気付くことが困難ですし、
監視ログからそれを探し出すにしても、しっかりとしたログ設計と分析体制を整えていなければ対応できません。
そして気付けないままある日、ユーザーからの問い合わせで発覚するという経験している方もいるのではないでしょうか。

転ばぬ先の杖ということでアプリケーション内部のパフォーマンス監視を行うためのマネージドサービスである AWS X-Ray をご紹介したいと思います。

== X-Rayとは

アプリケーションが処理するリクエストやレスポンスに関するデータを収集し可視化、分析するためのサービスです。
分散トレーシングに対応しているため複雑化したマイクロサービスであってもリクエストを追跡が可能で、
X-Ray SDKが対応している開発言語（環境）であれば、コードにはほぼ手を入れずにすぐに利用できます。

== X-Rayの画面

==== サービスマップ

ノード間の接続状態を表示します。
ノードの中央には平均レスポンス時間と１分間に送信したトレース数が表示され、レスポンス状態が円グラフに色分けして表示されます。
ノードまたは接続を表す矢印を選択することでヒストグラムが表示でき、
ヒストグラムをドラッグして範囲指定することでフィルタリングすることもできます。

//image[xray-11][サービスマップ画面]{
//}

==== トレース

上段にはリクエストURL別にグループ分けされたものが表示されており、上段のURLを選択することで下段のトレースリストがフィルタリングされます。
下段のトレースIDを選択することでトレース詳細画面に遷移します。

//image[xray-8][トレース画面]{
//}

==== トレース詳細

セグメントとサブセグメントの階層がタイムラインとして表示されます。
一番上が1回のリクエストで記録されたすべてのデータを表しており、その下にリソース別のサブセグメントが表示されます。
サブセグメントを選択することで注釈やメタデータ等の生データを参照することができます。

//image[xray-12][トレース詳細画面]{
//}

==== アナリティクス

応答時間や時系列等でフィルタリングを行い、該当するトレースデータにアクセスできます。

//image[xray-10][アナリティクス画面]{
//}

== X-Rayへトレースデータを送信する

トレースデータを送信する方法は３つありますが、これからいくつかの方法で実際にX-Rayにトレースデータを送信してみます。

今回はローカルにDockerコンテナでテスト環境を作るため、DockerとDocker Composeが必要になります。
インストール方法は以下の各公式サイトを参考にしてください。

 * Dockerのインストール@<br>{}@<href>{https://docs.docker.com/install/}
 * Docker Composeのインストール@<br>{}@<href>{https://docs.docker.com/compose/install/}

インストールが完了したらコマンドを叩いて、正常にインストールがされていことを確認しましょう。筆者の環境では下記のような表示になりました。

//cmd{
$ docker --version

Docker version 19.03.1, build 74b1e89

$ docker-compose --version

docker-compose version 1.24.1, build 4667896b
//}

X-Rayへアプリケーション側からデータを送信するにはX-Rayへの書き込み権限が必要になりますので、
必要なIAMポリシーをもったユーザーを作成します。
ユーザー名はxray-userとして、プログラムから利用するのでプログラムによるアクセスを選択します。

//image[xray-13][ユーザー作成ステップ１]{
//}

本来アクセス権は必要最小限に留めるべきですが、
今回はテスト用に短時間だけ利用するのでAdministratorAccessのポリシーをアタッチします。

//image[xray-14][ユーザー作成ステップ２]{
//}

アクセスキーIDとシークレットアクセスキーはテスト環境に認証情報を設定する際に使用しますので、一時的にどこかにコピーしておきます。
以上で、プログラムから利用するユーザー作成は完了です。

//image[xray-15][ユーザー作成ステップ３]{
//}

=== X-Ray SDKとX-Rayデーモンを利用する

デーモンの配置が必要ですが、SDKが対応している言語・環境であれば比較的かんたん@<fn>{xray-easy}に始められる方法です。
SDKで収集したデータは一旦デーモンにUDPで送信されバッファリングされたのち、デーモンがまとめてバッチ処理でAWSにデータを送信します。
これのおかげで、万が一、デーモンにトラブルが発生した場合でもアプリケーションの動作には影響がありません。
なお、AWS Lambdaで利用する場合は、デーモンをユーザー側で配置する必要はありません。

//footnote[xray-easy][かんたんではありませんでした！]

X-Ray SDKはJava、Go、Node.js、Python、Ruby、.NETに対応していますが、
ここでは、Node.jsを利用して送信してみます。

====[column] かんたんではなかったX-Ray SDK

Node.jsのX-Ray SDKでトレースデータの収集を行いましたが、
執筆を進めている中でSDKが下記のような不可解な動作をしており、原因検証が執筆期間内で十分行えませんでした。
@<br>{}
@<br>{}
１．なぜかSQLクエリがトレースデータに入らない
@<br>{}
２．外部HTTPリクエスト、AWS SDKのトレースデータが1リクエスト内で１度しか取れない
@<br>{}
@<br>{}
「なぜかSQLクエリがトレースデータに入らない」については手動でトレースデータを収集することで対応する記事にしておりますが、
２番目ついてはコード修正が間に合わずAWS SDKのトレースは１度しかできないコードになっております。すみません。
手動でトレースデータを作成するという手間がかかるため、X-Ray SDKの自動トレースでかんたんに導入とは言えなくなってしまいました。
どなたか回避方法をご存じの方がいらっしゃいましたら、そっと教えていただけると嬉しいです・・・

====[/column]

SDKは各ライブラリをラッピングしてトレースデータを収集するため、限られたライブラリのみ対応しています。
各言語の対応環境の詳細については、X-Rayの開発者ガイドなどを参照してください。

 * @<href>{https://docs.aws.amazon.com/ja_jp/xray/latest/devguide/aws-xray.html}

Node.jsのサンプルコードは下記GitHubリポジトリで公開しています。

 * @<href>{https://github.com/takaaki-s/xray-nodejs-example}

今回のテスト環境は下記のようにコンテナを定義しました。

//list[nodejs-dockercompose][docker-compose.yml]{
version: '3.7'
services:
  nodejs:
    image: node:12-alpine
    init: true
    depends_on:
      - db
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
      - '3306:3306'
    environment:
      MYSQL_ROOT_PASSWORD: password
      MYSQL_DATABASE: xray_example
    command: mysqld --character-set-server=utf8mb4 --collation-server=utf8mb4_unicode_ci
    volumes:
      - ./db-data:/var/lib/mysql
  xrayd:
    build: ./docker/xrayd
    volumes:
      - ./.aws:/root/.aws
    expose:
      - '2000'
    environment:
      - AWS_REGION=ap-northeast-1
  # awsコマンドを実行するためのコンテナ
  # 常時起動はせずにawsコマンド実行時のみ起動させます
  awscli:
    build: ./docker/awscli
    volumes:
      - ./.aws:/root/.aws
//}


まずは、AWSの認証情報をこのテスト環境に設定します。
下記コマンドを実行して、先ほど作成したユーザーのアクセスキーとシークレットアクセスキーを設定してください。
リージョンはap-northeast-1（東京）を指定してください。

//cmd{
$ docker-compose run --rm awscli aws configure

AWS Access Key ID [None]: <あなたのアクセスキー>
AWS Secret Access Key [None] <あなたのシークレットアクセスキー>
Default region name [None]: ap-northeast-1
Default output format [None]: 何も入力せずにENTER
//}

認証情報の設定ができたらテスト環境を起動します。

//cmd{
$ docker-compose up -d
//}

コンテナが起動したらDBのマイグレーションと初期データの投入を行います。
DBコンテナの起動に時間がかかる場合がありますので、エラーが出る場合は少し時間をおいてください。

//cmd{
$ docker-compose exec nodejs npx knex migrate:latest

Using environment: development
Batch 1 run: 2 migrations

$ docker-compose exec nodejs npx knex seed:run

Using environment: development
Ran 2 seed files
//}

DBマイグレーションの完了後、
http://localhost:3000/にアクセスして、このような画面が出ればセットアップ完了です。

//image[xray-6][http://localhost:3000/]{
//}

すでにX-Rayへトレースデータが送信されており、X-Rayのコンソール画面で送信された情報が参照できるようになっていると思います。
次に、どのようにX-Rayへトレースデータを送信しているのかExpress、MySQL、外部HTTPリクエスト（axios）、AWS-SDKそれぞれコードを抜き出して見ていきます。

==== Express

ルート定義の前後でSDKから返されるミドルウェアをそれぞれ設定します。
これでリクエストからレスポンスまで自動的に計測されます。
セグメント名はフィルタリングしやすいようにドメインやAPI名等設定するのが良いでしょう。

//list[appjs-express1][app/app.js]{
const express = require('express');
const app = express();
app.set('view engine', 'ejs');

app.use(AWSXRay.express.openSegment('MyApp'));

/** この間にルート定義を書きます */

app.use(AWSXRay.express.closeSegment());
app.listen(3000);
//}

Expressのルート定義の中で、トレースデータを取得できるようになりましたが、
この中で、さらに詳細な処理単位でトレースしたい場合もあると思います。
その場合は、サブセグメントを生成することで更に小さい単位でトレースデータを記録することが可能です。
さらに、addAnnotationやaddAttributeメソッドを使うことで付加情報もトレースデータに含めることができます。

//list[appjs-express2][app/app.js]{
const parentSeg = AWSXRay.getSegment();
// レンダリング時間を計測するためサブセグメントを生成
const seg = parentSeg.addNewSubsegment('render');
res.render('./index.ejs', {
  books,
  author: req.query.author,
  title: req.query.title,
});
// Key:Value形式で注釈を入れることが可能です
// seg.addAnnotation({key: 'value'});
// 同じ用にメタデータを入れることが可能です
// seg.addAttribute({key: 'value'});
seg.close();
//}

==== MySQL

本来SDKのライブラリキャプチャでSQLクエリまで取得できると思うのですが、今回はうまくいかなかったため手動でSQLクエリを取得しています。
そのため、かんたんに導入と書いたもののかなりコード量が増えてしまいました。（ほんとすみません）

まず、ライブラリをキャプチャするためにmysqlライブラリをSDK経由でインポートします。
次に、クエリーを発行する場所でサブセグメントを生成しクエリー実行後に生成したサブセグメントをクローズしています。

//list[appjs-mysql1][app/app.js]{
const mysql = AWSXRay.captureMySQL(require('mysql'));

const conn = mysql.createConnection({
  host: 'db',
  port: 3306,
  user: 'root',
  password: 'password',
  database: 'xray_example',
});
conn.connect();

const parentSeg = AWSXRay.getSegment();
// queryが非同期関数のためPromiseでラッピングした関数を利用します
const books = await queryHelper(
  conn,
  parentSeg,
  'SELECT b.title,a.author_name as author FROM books b INNER JOIN authors a ON a.id= b.author_id'
);
conn.end();

const queryHelper = (conn, parentSeg, query, params = []) => {
  const config = conn.config;
  // SDKではSQLクエリがうまく収集できなかったため、手動でサブセグメントを生成しています。
  const seg = parentSeg.addNewSubsegment(`${config.database}@${config.host}`);
  // サブセグメントフィールドにSQLクエリ情報をセット
  seg.addSqlData({
    url: `${config.host}:${config.port}/${config.database}`,
    user: config.user,
    sanitized_query: query,
  });
  seg.namespace = 'remote';

  var session = AWSXRay.getNamespace();
  session.run(() => {
    AWSXRay.setSegment(seg);
  });

  return new Promise((resolve, reject) => {
    conn.query(query, params, (err, rows) => {
      if (err) {
        seg.close(err);
        reject(err);
      }
      seg.close();
      resolve(rows);
    });
  });
};
//}

==== 外部HTTPリクエスト

AWSXRay.captureHTTPsGlobalメソッドを使って、
httpとhttpsライブラリをキャプチャすることでaxiosのリクエストをトレースすることができますが、
今回、検証を行った中ではExpressの1リクエスト内で外部HTTPリクエストと後述のAWS SDKいずれか1度目のトレースデータ以外取得することができませんでした。
MySQLの場合と同様にサブクエリを生成して手動でトレースデータを作成することで対応しています。

//list[appjs-express3][app/app.js]{
// 手動でトレースデータを生成しているためSDKでのキャプチャをしていない
// AWSXRay.captureHTTPsGlobal(require('https'));
// AWSXRay.captureHTTPsGlobal(require('http'));

const axios = require('axios');
await requestGetHelper(parentSeg, 'https://www.google.co.jp/');

requestGetHelper = async (parentSeg, uri) => {
  const url = require('url');
  const options = url.parse(uri);

  const seg = parentSeg.addNewSubsegment(
    options.hostname || options.host || 'Unknown host'
  );
  const res = await axios.get(uri);
  seg.close();
  // サブセグメントフィールドにリクエスト情報をセット
  const { request } = res;
  seg.addRemoteRequestData(request, res.request.res, false);
  seg.namespace = 'remote';
};
//}

==== AWS SDK

AWS SDKをキャプチャすることで、AWSに対するAPIコールをトレースすることができますが、
今回の検証では複数回トレースデータを取得することができませんでした。
前項の外部HTTPリクエストのように手動でセグメントデータを生成することで、
対応可能と思われますが執筆期間中には間に合わせることができませんでした。申し訳ありません。

//list[appjs-express4][app/app.js]{
const AWS = AWSXRay.captureAWS(require('aws-sdk'));

const s3Client = new AWS.S3({region:'ap-northeast-1'});
const bukets = await s3Client.listBuckets().promise();
//}

=== X-Ray SDKの対応していない環境で利用する

X-Ray SDKが対応していない言語や環境の場合はAWS SDKを利用して直接データを送信するか、
生成したトレースデータをUDPでデーモンに送信します。
今回は、PHPとLaravelの環境でトレースデータの収集しデーモンへ送信してみましょう。
PHPのサンプルコードは下記GitHubリポジトリで公開しています。
また、サンプルコードでは有志の方が公開されているライブラリ@<fn>{pkerrigan}を利用させていただきました。

 * @<href>{https://github.com/takaaki-s/xray-php-example}

//footnote[pkerrigan][https://github.com/patrickkerrigan/php-xray]

テスト環境の構築はNode.jsと同様、Docker Composeでコンテナを起動するところまでは同じです。
コンテナが起動したら下記シェルスクリプトを実行することで初期設定が完了します。完了後にhttp://localhost:8080/にアクセスするとNode.jsと同様の画面が表示されたら環境の構築は完了です。

//cmd{
$ bash init_development.sh
//}

X-Ray SDKの自動トレースが利用できない場合は、
計測したい場面でセグメントやサブセグメントを生成して送信するという流れになります。
自動トレースがないので、どこにデータを収集処理を仕込むかが導入の手間を減らすポイントになりますが、
フレームワークを利用している場合はミドルウェアに仕込むのがオーソドックスなパターンではないでしょうか。
今回のサンプルプログラムでもLaravelのミドルウェアにトレース開始の処理をはさんで自動トレースを行うようにして、
さらにDBのイベントをフックしてサブセグメントを生成するような処理にしました。

//list[xray-laravel1][/xray/app/Http/Middleware/XrayCapture.php]{
public function handle($request, Closure $next)
{
    Trace::getInstance()
        ->setTraceHeader($_SERVER['HTTP_X_AMZN_TRACE_ID'] ?? null)
        ->setName('app.example.com')
        ->setUrl($_SERVER['REQUEST_URI'])
        ->setMethod($_SERVER['REQUEST_METHOD'])
        ->begin(100);

    DB::listen(function ($query) {
        $sql = $query->sql;
        foreach ($query->bindings as $value) {
            $sql = preg_replace("/\?/", $value, $sql, 1);
        }

        Trace::getInstance()
            ->getCurrentSegment()
            ->addSubsegment(
                (new MySqlSegment())
                    ->setName('db.example.com')
                    ->setDatabaseType('MySQL')
                    ->setQuery($sql)    // Make sure to remove sensitive data before passing in a query
                    ->begin()
                    ->end($query->time / 1000)
            );
    });

    return $next($request);
}

public function terminate($request, $response)
{
    Trace::getInstance()
        ->end()
        ->setResponseCode(http_response_code())
        ->submit(new DaemonSegmentSubmitter("xrayd"));
}
//}


=== AWS CLIを利用する

送信データをjson形式で用意しないといけない部分が面倒ですが、
例えば下記のようなシェルスクリプトを用意することで、シェル内から比較的かんたんに送信することが可能です。
デーモンを経由せずに直接X-Rayに送信していますので
ローカルでのアプリのビルド時間や、CodeBuildでCI/CDの実行時間などをトレースして監視するのも面白いかもしれません。

//list[xray-awscli][xray_putsegment.sh]{
#!/bin/sh
HEX_TIME=$(printf '%x\n' $1)
GUID=$(dd if=/dev/random bs=12 count=1 2>/dev/null | od -An -tx1 | tr -d ' \t\n')
TRACE_ID="1-$HEX_TIME-$GUID"
END_TIME=$(date +%s)
SEGMENT_ID=$(dd if=/dev/random bs=8 count=1 2>/dev/null | od -An -tx1 | tr -d ' \t\n')
DOC="{\"trace_id\": \"$TRACE_ID\", \"id\": \"$SEGMENT_ID\", \"start_time\": $1, \"end_time\": $END_TIME, \"name\": \"$2\"}"
aws xray put-trace-segments --trace-segment-documents "$DOC"
//}

//cmd{
$ export START_TIME=$(date +%s)

# 計測したい何らかの処理

$ ./xray_putsegment.sh $START_TIME buildtime
//}

== さいごに

ここまでX-Rayの導入方法を駆け足で解説してきましたが、
X-Rayでトレースデータの収集を行うことで、アプリケーション内部の動きを可視化することができるようになりました。
次のステップとして、可視化されたトレースデータを使ってボトルネックの特定・改善に役立ててみたり
CloudWatchとSNSを組み合わせて、あるAPIのレスポンスタイムが落ちてきた際に通知を出す等するのも良いかもしれません。

== 用語

 * セグメント
 ** トレースデータはこのセグメント単位で送信されます。
 * サブセグメント
 ** セグメントの中のさらに処理単位で詳細な記録を残したい場合はサブセグメントとして記録できます。
 * 注釈
 ** セグメント、サブセグメントに付加情報として記録できるkey:value値。X-Rayコンソール画面でフィルタフィングができます。
 * メタデータ
 ** セグメント、サブセグメントに付加情報として記録できるkey:value値。注釈と違ってフィルタリングができません。

