= AWS認定ソリューションアーキテクト - アソシエイト 試験の心構え編

ここからは、試験について、知っておくといい予備知識を経験を元に語っていきます。
私の実績は、去年の10月にAWS認定ソリューションアーキテクト- アソシエイト（以降、AWS認定SA）を受けて831点で合格しました。1000点満点中760点で合格です。
分野別の出題傾向の分野3と分野4は知識が足りていないと評価されましたので、まだまだ勉強不足と感じています。

== 合格した際の特典について

AWS認定SAに合格すると、4つの特典を受けることができます。

 1. 模擬試験の無料バウチャー
 2. 専用ストアーにて、専用のグッズを購入できます。
 3. 問題作成の手伝いができます。
 4. 次回、本試験を受ける際に受験料が50%引きとなるバウチャー

私個人としては模擬試験の無料バウチャーが魅力的かと思います。
AWS認定SAに合格した後、次に狙うのは「AWS認定プロフェッショナル」です。
AWS認定プロフェッショナルの模擬試験料4,000円が浮くことはとても嬉しいです。
また、AWS認定は3年ごとに認定を更新する（再認定を受ける）必要があります。
50%の割引バウチャーコードを使用すると現行の試験が50%引きで受験でき、それによって認定を更新できます。

特典ではありませんが、デジタルバッチを表示できます。
最近デザインが変わって、明るい感じのバッチに変更されました。

//image[AWS-SA-badge][AWS認定SAバッチ]{
//}

デジタルバッチは、メールの署名欄やSNSのプロフィールなどに使用でき認定を受けているという証拠となります。
ドヤ顔で色んな所で利用しています。
実は私のチームは「今年の6月中に全員がAWS認定SAに合格する。」という目標を立てています。
6月にはドヤ顔できなくなりそうですので、いち早くプロフェッショナルを取得しドヤ顔を継続できるように勉強中です。

== サンプル問題と模擬試験

以下のページからサンプル問題をダウンロードできますので、そちらを解いてみてください。10問しかないのが残念ですが雰囲気は味わえます。
@<br>{　}

@<href>{https://aws.amazon.com/jp/certification/certified-solutions-architect-associate/, https://aws.amazon.com/jp/certification/certified-solutions-architect-associate/}
@<br>{　}

模擬試験は、受けることをオススメします。
2,000円かかりますが模擬試験では実際の試験問題に近い問題が25問出題されます。
どの問題が正解したかや間違ったかを知ることはできませんが、どの分野が理解できているかをとてもざっくりとした成績表で教えてくれます。
知識が足りない分野を復習することで、万全の体制を取ることができます。

 模擬試験は、複数回受けてもまったく同じ問題が出題されたと報告を受けました。
ですので、複数回受ける必要はありません。
@<br>{　}

この方法は、いいのかわかりませんが、TIPSとして！
@<br>{　}

模擬試験は、自分のPCで受けることができます。そこで模擬試験の問題をキャプチャして、
後からじっくりと問題を解くのは1つの手かと思います。せっかく2,000円出して受けるんです。
最大限利用しない手はありません。なお、問題を公表したりするのは禁止されているので、
撮ったキャプチャはあくまでも個人的利用に留めるように！
模擬試験の復習では、「なぜ正解か？」と「なぜ間違っているのか？」を明確にして行くと効率が良いです。
なぜ間違っているかを知っているということは、とても重要です。
最後の問題の解き方でもありますが、正解に不安がある場合に間違っている回答を消去していく方法は、とても効率が良かったです。

== 分野別の出題傾向

//table[table1][テスト構成]{  
.	分野	割合
--------------------------------------------
分野1	回復性の高いアーキテクチャを設計する	34%
分野2	パフォーマンスに優れたアーキテクチャを定義する	24%
分野3	セキュアなアプリケーションおよびアーキテクチャを規定する	26%
分野4	コスト最適化アーキテクチャを設計する	10%
分野5	オペレーショナルエクセレンスを備えたアーキテクチャを定義する	6%
//}

== 試験はいつでも受けられる

注意する点として、予約は3日前ぐらいにしないといけません。
試験会場によっては、土日は行っていなかったり、特定の曜日が休みだったりします。
前もって、どこの試験会場で受けるのか決めておくといいかもしれません。
私は、先に受験された方に進められて、@<href>{https://cbt-s.com/kabukiza-tc/, 銀座CBTS歌舞伎座テストセンター}で受験しました。
とてもきれいで、オススメです。（ただし、その他の試験会場に行ったことはない。）
@<br>{　}

@<href>{https://cbt-s.com/kabukiza-tc/, https://cbt-s.com/kabukiza-tc/}

== 問題数は65問、時間は130分

公式には問題数は明記されていませんが、私が受けたときは65問でした。
余裕を持った時間配分が大事かと思います。
仮に65問だとして、1問2分のペースで解くとぎりぎりの時間配分となります。20分ぐらい余裕を見れるといいかもしれません。
経験ではすべての問題を解き終わった後は、回答に不安のある問題を順に解きなおしました。
何度見てもわからない問題はあるもので、そういった問題はきっぱりあきらめて、他の回答に不安のある問題を再確認、少し時間があったので最後に最初から問題を確認しました。

== 問題の解き方

まず試験では、試験問題にフラグを立てることができます。
フラグを立てた問題は、視覚的に分かるようになっており後から見直すことができます。
問題の移動は自由に行うことができます。
回答した問題にはロックがかかるようになっているので、回答を変更したい場合はロックを外してから回答を変更することになります。

問題の正解がわからない場合は、間違いの答えを消去していく！これが結構消去できるんです。
未回答は１番ダメです。回答がどうしてもわからない場合は、消去して残りの回答から適当に答えを選び、問題にフラグを立てておく！
全問解いた後で、設問へ戻ることができるので、そこで改めてフラグを立てた問題を解いてみる。
1問2分程度しか考える時間がないのでペースが崩れると大変です。

== 試験対策の教材

=== 本を読む

なんとなくAWSを利用している場合は、知識を整理するために本を読むといいです。私はなんとなく派でしたので本を読んですっきりしました。
VPC、セキュリティーグループやインターネットゲートウェイなどは、特に良くわからなかったので大変助かりました。
本についてはAmazonで2冊ほど出版されているようです。どちらも良い参考書ですので自身に合う方を選べばよいかと思います。

=== 実際に手を動かす

やはり、実際にGUIをポチポチすると理解が早いです。ほんの少しだけ重い手を動かしてみるとかえって効率的に習得できます。
仕事でCloudFormationを利用する機会が増えてきているのですが、設定が難しい。そんな時にはGUIで確認をしながら設定を書いています。

=== AWSのよくある質問を見る

この試験の勉強をして知ったのですが、AWSのFAQは良くできています。
ものすごい数があるので、各APIのよくある質問は一度目を通すといいです。
以下はEC2のよくある質問のURLです。URLのAPI名を変えれば各APIのよくある質問を開けます。
@<br>{　}

@<href>{https://aws.amazon.com/jp/ec2/faqs/, https://aws.amazon.com/jp/ec2/faqs/}

=== AWSホワイトペーパーを読む

AWSホワイトペーパーには、AWS、独立アナリスト、AWSコミュニティによって作成された技術的な文章。また、
AWSアナリストレポートで、業界アナリストが執筆したレポートなどがあります。ボリュームは満点ですが、気になる箇所だけでも読んでおくと良いです。
@<br>{}

@<href>{https://aws.amazon.com/jp/whitepapers/, https://aws.amazon.com/jp/whitepapers/}
