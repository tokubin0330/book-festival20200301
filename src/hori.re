= 100円でお釣りがくる！？実践WordPress静的ホスティング

== はじめに

私自身、WordPressでの開発・運用を10年近くに渡って携わって来ましたけど、ひたすらG社のレンタルサーバーを愛用してまいりました。
 その理由はただ一つ！！
 
「安い！！」「楽だ！！」「ボタン１つでWordPressインストールできるから！！」
 
そもそもWordPressで運用しているサイトは、大多数は耐久性や可用性に関する考慮は正直あまり必要ないという点はあります。
正直私自身もAWSでWordPressを運用するのは、余程のPVを集めるサイトではないとその必要がないと思ってきました。ところがここ数年AWSを勉強していくにしたがって、AWSでも安くWordPressの運用ができるのではないかという可能性を感じるようになりました。
この章では、AWSを使用したWordPressの静的化と、そのデメリットとデメリットを実際に検証した結果を元に書いていきます。

== 静的化に当たって

=== なぜWordPressを静的にするの？

 【セキュリティ】
 @<br>{}　
 静的サイトは基本的にセキュリティ面では安全だと言えます。WordPressを静的サイトにした場合でも、WordPressで使われるプラグインも全て静的なファイルに書き換えられるので、安全性が高くなります。
 また、アップデート・ハッカー・メンテナンス・スクリプトの破損・悪いプラグインなどについて心配する必要は全くないので静的化にした方が安心にサイトの運用をする事ができます。

 【スピード】
 @<br>{}　
 当たり前の話になりますが、静的ファイルは動的ファイルよりも速くロードされます。PHPの実行とデータベースへのアクセスも無いので、スピードが俄然速くなります。

 【コスト】
 @<br>{}　
 要求を処理するために必要なサーバーの通信時間は少なくなるので、静的にした方が安くなります。特にトラフィックが多い場合は、コスト削減の恩恵を沢山受けられます！！！

ポートフォリオや個人的なWebサイトを運営している場合は、HTMLとCSS（そして多少のJavaScript）のみで構成されているとすると、その場合も静的化をする事によって多くのメリットを得る事ができます。この章の後半では、実際に静的にした場合に、どれぐらいのコスト削減ができるかの検証結果を掲載します。


== DockerでWordPressを構築する

以下の手順でDocker環境を作っていきます。

 1. 空のプロジェクトディレクトリを作成します。
 2. そのディレクトリに移動します。
 3. リスト 5.1でdocker-compose.ymlというファイルを作成します。
 4. プロジェクトディレクトリで、次のコマンドを実行します。

//cmd{
    docker-compose up -d
//}

 * この時点でWordPressはlocalhostでアクセス可能になるでしょう。
 
 * localhost/wp-adminに移動してWordPressの設定を開始します。
 
 * 注：dockerコンテナーをシャットダウンするには以下を実行してください。
 
//cmd{
    docker-compose down --volumes 
//}

 
これで、Webサイトを変更する準備が整いました。
@<br>{}　
//list[viewer_docker-compose][docker-compose.ymlファイル]{
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
WordPressサイトをホスティングすることはセキュリティー上、完全に安全とは言えませんし、費用もそれなりにかかります。
静的にすることはこれらの欠点を最適化するためには素晴らしい方法だと思われます。
そして、それをS3でホストすることはさらにコストを削減し、よりきめ細かいセキュリティ設定を可能にする事ができます。

以下の手順では、WordPressサイトから静的ファイルを生成し、それらをカスタムドメイン用に新しく構成されたAWS S3バケットでホストする方法について説明します。

 1. 「プラグイン」 > 「新規追加」 > wp2staticを検索 >「インストール」 >「有効化」の順にクリックします。プラグインが有効になったら、サイドパネルのwp2staticに移動してDeploy static websiteタブを選択します。
 2. タブの下にWhere will you host the optimized version of your site?のところにZIPアーカイブを選択します。次に保存をクリックします。
 3. Destination URLのところにS3に紐ついてるDomain名を入れます。
 4. Start static site exportを押すとzipで静的ファイルのダウンロードできます。

//image[wp2static][wp2staticプラグイン][scale=0.8]{
//}

//image[static_export][static export][scale=0.8]{
//}
 

=== S3バケットの設定

 AWSにサインインします。S3に移動して新しいバケットを作成して、ドメインの名前を付けます。今回の例はshowcase-tv.comです。

//image[02_bucket_name][バケットの作成][scale=0.8]{
//}

 次に、バケットポリシーを作成する必要があります。AWSには便利なポリシージェネレータがあります。
 ポリシージェネレータを使用したくない場合でも、AWSのドキュメントには分かりやすい例が記載されています。
 パケットポリシーを以下のように設定してください

//image[04_bucket_policy][バケットポリシー][scale=0.8]{
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

 安全を期すために、すべてのGETリクエストがドメインにアクセスすることを許可する1つのルールを持つCORS構成を追加することをお勧めします。上記の例の場合はhttps://showcase-tv.comです。


//image[05_CORS_setting][CORSの設定][scale=0.8]{
//}

 S3のバケットのページからプロパティのページへ移動してホスティング機能を有効にします。

//image[03_staticweb_hosting][ホスティングの設定][scale=0.8]{
//}

 wordpressからダウンロードしたWebサイトファイルをs3 bucketにアップロードします。

//embed[latex]{
\clearpage
//}

== WordPressの静的化検証

=== 検証にあたって

今回、WordPressの静的化の検証実験を行なうに当たって、ネパール出身のメンバーが個人的に運用しているサイトを実際に使う事にしました。
現在、このサイトは静的ファイルで運用されているので、実際にアクセスして頂いてスピード感などを実感して頂けたらと思います。

http://janasahayog.com

=== 検証実験詳細

静的化を行なったサイトを15日間の期間でS3の運用費を測定したところ以下のようになりました。この金額はAWSサミットで貰ったクレジットが適用されていルため、引かれている金額が表示されています。

//image[S3_2][S3料金][scale=0.8]{
//}

=== ec2・レンタルサーバーとの比較

今回検証に使ったサイトは元々ec2のt2.microインスタンスを使って運用されていました。
1ヶ月間運用した際に、t2.microで運用した場合と静的化した場合を比較した結果が以下になります。

//table[ec2_s3_price][ec2と静的化の比較]{
type 	月間推定費用
---------------------------------
ec2_t2.micro 	$10.944
S3 	$0.48
//}

//list[ec2][ec2との比較]{
  * ec2で運用した場合と比較して静的化した場合は月間で約95%のコスト削減に成功する事が確認できました。
//}

また、私が良く使っているG社のレンタルサーバーと比較してみると以下のような結果になります。【1ドル108円で計算】

//table[rental_s3_price][レンタルサバーと静的化の比較]{
type 	月間推定費用
---------------------------------
レンタルサーバー 	¥205	
S3 	¥52
//}

//list[rental][レンタルサーバーとの比較]{
  * ec2で運用した場合と比較して静的化は約75%のコスト削減に成功する事が確認できました。
//}


=== PVが多いサイトを静的化した時の予想コスト

S3でWordPressを静的化を検証するに当たって、PVが多いサイトを想定したコスト計算をしてみたところ以下のような結果になりました。

//list[S3_cost][S3のコスト例]{
  
  月間に10万PVのサイトを運営したとしてもかかるS3のコストは$1.96/月、約200円/月になります。私が勤めている会社では80万PV/月のメディアをWordPressで運用していますが、4台のec2で動かしてec2のみのコストは月に約$280掛かっています。

  上記の計算によると80万PVだと静的化した場合は推定$15.68になって、現在のec2のコストの約6%になります！！！

//}


== WordPressの静的化に当たっての課題

今回Wordpressの静的化について色々と検証してきましたが、サイトを静的する事によってサイト運営費のコスト削減やサイト表示スピードを速める事はできたとしても
問い合わせ機能や他の様々なプラグインが使えなくなってしまいます。


== まとめ

今回はWordPressを静的化してS3で運用した時とec2や一般のレンタルサーバーで運用した時のコストを比較して検証して見ました。検証の結果としては、問い合わせフォームやサイト内検索機能等を実装するためにはlambdaやapi gatewayを使って実装する必要はあるものの、サイト自体は静的化によってかなりのコスト削減ができることは確認できました。

WordPressの静的化に関しては以下のような静的化ホスティングを可能にするサービスが登場しました。

//embed[latex]{
\clearpage
//}

//list[Shifter_URl][Shifter]{
  * Shifter
  https://www.getshifter.io/

  *Shifterの特徴としては
  1. 静的コンテンツがCDN上で配信されるので爆速。
  2. 静的化サイトでありながらも、問い合わせフォームプラグイン（ContactForm7）を使う事ができる
　
  Shifterの価格は以下のようになっています。
//}

//image[Shifter][Shfiterの価格][scale=0.6]{
//}

//list[hardpress][Hardpress]{
  * Hardypress
  https://www.hardypress.com/

  * Hardypressの特徴としては
  静的化サイトでありながらも、問い合わせフォーム(ContactForm7)やサイト内検索機能や他のプラグインも利用する事ができます。

  Hardypressの価格は以下のようになっています。
//}

//image[hardypress][Hardypressの価格][scale=0.6]{
//}

今回AWSを利用してのWordPressを静的化について検証してきましたが、正直なところ現時点では上記のShifterやHardypressには勝る事ができないと言うのが現実かもしれません。

次回の技術書典までに、AWSの特徴を活かしてShifterよりも機能が充実している、プラットフォームの製作を目指していきたいと思います。

製作の進捗はこちらで公開しています、ぜひご確認ください！！

https://www.facebook.com/ramesh.giri.90260
