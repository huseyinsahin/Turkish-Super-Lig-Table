# Türkiye Super Lig Tablosu / Turkish Super Lig Table 
Bu projede Türkiye Süper Lig takımlarının maç sonuçlarını klavyeden yada dosyadan okuyarak lig tablosunu oluşturan bir program istenmektedir.  / This project in Turkey Super League teams match results creates the league table by reading it from the keyboard or file is requested.

## Proje Özellikleri / Project Features
* Ligte 10 takım bulunmaktadır. Bu sayı gerekirse değiştirilebilir. / There are 10 teams in the league. This number can be changed if necessary.
* Galibiyet için 2 puan, beraberlik için 1 puan ve mağlubiyet için -1 puan kazanılır. Gerekirse bu değerler program üzerinden ya da "ayarlar.txt" dosyasından değiştirilebilir. / The team gets 2 points for a win, 1 point for a draw and -1 point for a loss. These values can be changed through the program or from the "ayarlar.txt" file.
* Her takımın tek bir karakterden oluşan takma ismi ve en fazla 12 karakterden oluşan takım uzun ismi bulunmaktadır. Takımların takma isimleri ‘A’, ‘B’, ‘C’, ‘D’, ‘E’, ‘F’, ‘G’, ‘H’, ‘I’, ‘J’ şeklinde olmalıdır. Takımların uzun isimleri “takimlar.txt” dosyasından okunmaktadır. / Each team has a single nickname and long names of the teams maximum of 12 characters long. The nicknames of the teams should be like 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'. Long names of the teams are read from the file "takimlar.txt".
* Program oynanan maçları klavyeden veya dosyadan giriş olarak alıp puan durumu tablosunu güncellemek amacıyla kullanır. / The program takes the matches played as input from the keyboard or file and uses them to update the standings table.
* Klavyeden maç girişi yapıldığında “A 5 C 3” şeklinde olmalıdır. Bunun anlamı A takımı ile C takımı maç yapmış, ev sahibi takım A takımı 5 gol atmış ve misafir takım C ise 3 gol atmıştır. / When a match is entered from the keyboard, it should be "A 5 C 3". This means that team A and team C have played matches, home team team A has scored 5 goals and guest team C has scored 3 goals.
* Dosyadan giriş yapıldığında ise her bir satır klavyeden yapılan giriş formatında olacaktır. Yani dosyada birden çok maç sonucu olabilir. / When entering from the file, each line will be in the input format made from the keyboard. So there can be more than one match result in the file.
* Oynanan maç bir kez daha giriş olarak verildiğinde ekrana uyarı vermektedir ve bu maç paun durumu tablosuna işlenmemektedir. A ve C takımı A takımının evinde sadece bir kez maç oynamalıdır. / When the played match is given once again as an entry, it warns the screen and this match is not recorded in the table of the score. Team A and C must play only once in team A's home.
* Puan durumu tablosu ekrana veya dosyaya puan sırasına göre, takımların alfabetik sırasına göre ya da takma isim sırasına göre ekrana yazılabilmektedir. İstendiğinde takım isimleri büyük harf olarak ekrana yazılabilmektedir. / The standings table can be written to the screen or file in order of points, in alphabetical order of the teams, or in order of aliases. When requested, team names can be written on the screen or file in capital letters.
* Ligdeki takım sayısı, galibiyette, mağlubiyette ve beraberlikte alınacak puan sayısı "ayarlar.txt" dosyasından okunmaktadır. / The number of teams in the league, the number of points to be won in a win, a loss and a draw is read from the "ayarlar.txt" file.
* Puan durumu tablosunda bulunan özellikler şunlardır / The features available in the standings table are :
    1. Takma isim - A, B, C gibi / Aliases - A, B, C, etc.
    2. Takım Uzun ismi, 12 karakter / Name of the team, 12 characters
    3. Oynadığı maç sayısı / Total matches played
    4. Galibiyet sayısı / Wins
    5. Beraberlik sayısı / Draws
    6. Mağlubiyet sayısı / Losses
    7. Attığı gol sayısı / Goals Scored
    8. Yediği gol sayısı / Goals Allowed
    9. Averaj / Goal Difference
    10. Puan / Points 
## Proje için Ön Şartlar / Project for Prerequisites
* Bilgisayarınızda gcc derleyicisi kurulu olmalıdır. / Gcc compiler must be installed on your computer.
* Visual Studio Code, Eclipse, Sublime Text, Atom, CodeBlocks vb. IDE veya editör kurulu olmalıdır. / Visual Studio Code, Eclipse, Sublime Text, Atom, CodeBlocks etc. IDE or editor must be installed.
* Aşağıdaki tablodaki gibi dosyalar oluşturulup proje ile aynı dizine konmalıdır. / Files as in the table below should be created and placed in the same directory as the project.

| Files  | File Content | Explanation |
| ------------- | :-------------: | :-------------: |
| ayarlar.txt  | 10 <br> 2 <br> 1 <br> -1 | Takım Sayısı / Number of team <br> Galibiyet Puanı / Win Score <br> Beraberlik Puanı / Draws Score <br> Mağlubiyet Puanı / Loss Score |
| takimlar.txt  | Galatasaray <br> Fenerbahce <br> Besiktas <br> Trabzon <br> Gumushane <br> Siran <br> Barcelona <br> Realmadrid <br> Liverpool <br> Juventus  | Programda yukarıdan aşağı sırası ile alfabetik takma isim veriliyor.('A','B','C',vb.) / In the program, alphabetical nicknames are given in order from top to bottom ('A', 'B', 'C', etc.) |
| maclar1.txt  | A 2 B 2 <br> A 3 C 3 <br> A 3 D 3 <br> B 0 C 0 | Maç sonuçları / Match results |

## Projeyi Çalıştırma / Running the Project
<pre>gcc turkish_super_lig.c -o turkish_super_lig
./turkish_super_lig
![](https://github.com/huseyinsahin/Turkish-Super-Lig-Table/blob/master/running_the_project.gif?raw=true)
