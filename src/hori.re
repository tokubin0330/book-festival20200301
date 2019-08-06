= AWSを使用して静的WordPressをデプロイする

== はじめに

私自身、WordPressでの開発・運用を10年近くに渡って携わって来ましたけど、ひたすら某G社のレンタルサーバーを愛用して来ました。
 
その理由はただ一つ！！
 
「安いから！！」「楽だから！！」
 
そもそもWordPressで運用しているサイトは、企業のコーポレートサイトなどが多いため耐久性や可用性に関する考慮は正直あまり必要ないという点はあります。
正直私自身もAWSでWordPressを運用するのは、余程のPVを集めるサイトではないとその必要がないと思ってきました。

ところがここ数年AWSを勉強していくにしたがって、AWSでも安くWordPressの運用ができるのではないかという可能性を感じるようになりました。
この章では、AWSを使用したWordPressの静的化と、そのデメリットとデメリットを実際に検証した結果を元に書いていきます。

== 静的化のメリット

=== なぜWordPressを静的にするの？

 1. 【セキュリティ】　静的サイトは基本的に安全です。Worpressを静的サイトにした場合でも、WordPressで使われるプラグインも全て静的なファイルに書き換えられるので、安全性が高くなります。
 また、アップデート・ハッカー・メンテナンス・スクリプトの破損・悪いプラグインなどについて心配する必要は全くないので静的化にした方が安心にサイトの運用をする事ができます。

 2. 【スピード】　当たり前の話になりますが、静的ファイルは動的ファイルよりも速くロードされます。PHPの実行とデータベースへのアクセスも無いので、スピードが俄然速くなります。

 3. 【コスト】　要求を処理するために必要なサーバーの通信時間は少なくなるので、静的にした方が安くなります。特にトラフィックが多い場合は、コスト削減の恩恵を沢山受けられるに間違いありません！！
この章の後半で実際に静的にした場合に、どれぐらいのコスト削減ができるかの検証結果を掲載します。

ポートフォリオや個人的なWebサイトを運営している場合は、HTMLとCSS（そして多少のJavaScript）のみで構成されているとすると、その場合も静的化をする事によって多くのメリットを得る事ができます。

== DockerでWordPressを構築する

以下の手順でDocker環境を作っていきます。

 1. 空のプロジェクトディレクトリを作成します。
 2. そのディレクトリに移動します。
 3. 以下の内容でdocker-compose.ymlというファイルを作成します。
 4. プロジェクトディレクトリで、次のコマンドを実行します。
    docker-compose up -d
 * この時点でWordPressはlocalhostでアクセス可能になるでしょう。
 * localhost/wp-adminに移動してWordPressの設定を開始します。
 * 注：dockerコンテナーをシャットダウンするには
    docker-compose down --volumes 
    を実行してください。
 5. これで、Webサイトを変更する準備が整いました。

//list[viewer_docker-compose][docker-compose.yml]{
{
version: '3.3'
 
services:
   db:
     image: mysql:5.7
     volumes:
       - db_data:/var/lib/mysql
     restart: always
     environment:
       MYSQL_ROOT_PASSWORD: somewordpress
       MYSQL_DATABASE: wordpress
       MYSQL_USER: wordpress
       MYSQL_PASSWORD: wordpress
 
   cli:
     image: wordpress:cli
     volumes:
       - ./site:/var/www/html/
   
   wordpress:
     depends_on:
       - db
     image: wordpress:latest
     ports:
       - "80:80"
     restart: always
     environment:
       WORDPRESS_DB_HOST: db:3306
       WORDPRESS_DB_USER: wordpress
       WORDPRESS_DB_PASSWORD: wordpress
 
volumes:
   db_data:
}
//}

=== 静的WordPressをダウンロードしてAWS S3にデプロイする
WordPressサイトをホスティングすることは安全ではなく、費用もかかります。
静的にすることはこれらの欠点を最適化するための素晴らしい方法です、そしてそれをS3でホストすることはさらにコストを削減し、よりきめ細かいセキュリティ設定を可能にします。

以下の手順では、WordPressサイトから静的ファイルを生成し、それらをカスタムドメイン用に新しく構成されたAWS S3バケットでホストする方法について説明します。

 1. 「プラグイン」 > 「新規追加」 > wp2staticを検索 >「インストール」 >「有効化」の順にクリックします。プラグインが有効になったら、サイドパネルのwp2staticに移動してDeploy static websiteタブを選択します。
 2. タブの下にWhere will you host the optimized version of your site?のところにZIPアーカイブを選択します。次に保存をクリックします。
 3. Destination URLのところにS3に紐ついてるDomain名を入れます。
 4. Start static site exportを押すとzipで静的ファイルのダウンロードできます。

//image[wp2static][wp2staticプラグイン][scale=1.0]{
//}

//image[static_export][static export][scale=1.0]{
//}
 

=== S3バケットの設定

 1. AWSにサインインします。S3に移動して新しいバケットを作成します。ドメインの名前を付けます。例えばshowcase-tv.comです。
 2. 次に、バケットポリシーを作成する必要があります。AWSにはこの便利なポリシージェネレータがあります。
 ジェネレータを使用したくない場合は、AWSのドキュメントにもかなり良い例があります。
 3. パケットポリシーを以下のように設定してください
 4. 安全を期すために、すべてのGETリクエストがドメインにアクセスすることを許可する1つのルールを持つCORS構成を追加することをお勧めします。この場合はhttps://showcase-tv.comです。
 5. S3のバケットのページからプロパティのページへ移動してホスティング機能を有効にします。
 6. wordpressからダウンロードしたWebサイトファイルをs3 bucketにアップロードします。

//image[02_bucket_name][バケットの作成][scale=1.0]{
//}

//list[viewer_generator][AWS Policy Generator]{

 Type of policy:：S3 Bucket Policy
 Effect: Allow
 Principal: *

 AWSサービス：Amazon S3（これはポリシーの種類に応じて自動的に設定されます）
 Actions：GetObjectのみ

 AmazonResourceName（ARN）：これはドメイン名に依存しますが、同じフォーマットになります。例えば：
 arn：aws：s3 :::showcase-tv.com/*

//}

//image[04_bucket_policy][バケットポリシー][scale=1.0]{
//}


//image[03_staticweb_hosting][ホスティングの設定][scale=1.0]{
//}

//image[05_CORS_setting][CORSの設定][scale=1.0]{
//}


== WordPressの静的化検証

=== 検証にあたって

今回、WordPressの静的化の検証実験を行なうに当たって、ネパール出身のメンバーが個人的に運用しているサイトを実際に使う事にしました。
現在、このサイトは現在静的ファイルで運用されているので、実際にアクセスして頂いてスピード感などを実感して頂けたらと思います。

http://janasahayog.com

=== 検証実験詳細

静的化を行なったサイトを15日間の期間でS3の運用費を測定したところ以下のようになりました。

//image[S3_price][S3料金][scale=1.0]{
//}

=== ec2・レンタルサーバーとの比較

今回検証に使ったサイトは元々ec2のt2.microインスタンスを使って運用されていました。
1年間運用した際に、t2.microで運用した場合と静的化した場合を比較した結果が以下になります。

//table[ec2_s3_price][ec2と静的化の比較]{
ネットワークACL	セキィリティグループ
---------------------------------
サブネット単位で影響	インスタンス単位で影響
許可/拒否をIN/OUTで指定可能	許可のみをIN/OUTで指定可能
ステートレスなため戻りの@<br>{}トラフィックも明示的に許可設定が必要	ステートフルなため@<br>{}戻りのトラフィックは考慮しなくてOK
設定の順番通りにルールが適用され@<br>{}ルールに適合したらそれ以上適用されない	すべてのルールが適用される
//}

また、私が良く使っている某G社のレンタルサーバーと比較してみると以下のような結果になります。

＊ここに表を作るよ！

== WordPressの静的化に当たっての課題

今回Wordpressを静的化について色々と検証してきましたが、サイトを静的する事によって問い合わせなどのような機能は
使えなくなってしまいます。

そのための対策として以下のような方法を検討します。


== まとめ

