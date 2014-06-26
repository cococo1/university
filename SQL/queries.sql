
SELECT Model, Viteza, Hd
FROM pc_uri
WHERE Pret<500



-- Asdasd
SELECT DISTINCT producator
FROM produse
WHERE Tip='Imprimante' 

-- Adaasd
SELECT model,Ram,Ecran
FROM laptop_uri
WHERE Pret>1000

-- Asd
SELECT *
FROM imprimante
WHERE Color='da'

-- Asd
SELECT model, viteza, hd
FROM pc_uri
WHERE Pret<600 AND (Cd='12x' OR Cd='24x')

-- Asd
SELECT Producator, Viteza
FROM produse, pc_uri
WHERE Hd in (SELECT MIN(Hd)
	 FROM pc_uri) AND
produse.Model=pc_uri.Model

-- Asd
SELECT produse.Model, Producator
FROM produse, imprimante
WHERE Pret>450 AND produse.Model=imprimante.Model

UNION

SELECT produse.model, Producator
FROM produse, pc_uri
WHERE Pret>450 AND produse.Model=pc_uri.Model

UNION

SELECT produse.model, Producator
FROM produse, laptop_uri
WHERE Pret>450 AND produse.Model=laptop_uri.Model

-- Asd
SELECT DISTINCT producator
FROM produse
WHERE produse.Tip='Imprimante' OR produse.Tip='laptop_uri'

EXCEPT

SELECT DISTINCT producator
FROM produse
WHERE produse.Tip='PC'

-- Asd
SELECT DISTINCT Producator
FROM produse
WHERE produse.Model IN (
SELECT Model
FROM pc_uri
WHERE Viteza>=450)

-- Asd
SELECT Model, Pret
FROM imprimante
WHERE Pret IN (
SELECT MAX(PRET)
FROM imprimante)

-- Asd
SELECT AVG(Viteza) AS Viteza_medie
FROM pc_uri
As
SELECT AVG(Viteza) AS Viteza_medie
FROM laptop_uri
WHERE Pret>1000

-- Asd
SELECT AVG(Viteza) AS Viteza_medie
FROM pc_uri,produse
WHERE pc_uri.Model=produse.Model AND produse.Producator='A'

-- Asx
SELECT DISTINCT produse.Model, producator
FROM pc_uri, produse
WHERE produse.Model=pc_uri.Model AND
Viteza>(
SELECT MAX(Viteza)
FROM laptop_uri)
As
SELECT DISTINCT produse.Model, producator
FROM pc_uri, produse
WHERE produse.Model=pc_uri.Model AND
Ram>(
SELECT AVG(Ram)
FROM laptop_uri)


-- Asd
SELECT DISTINCT Model, Pret
FROM laptop_uri 
WHERE 
Pret/2>(
SELECT MIN(Pret)
FROM pc_uri)



-- Asx
SELECT Viteza,AVG(Pret)
FROM pc_uri
GROUP BY Viteza

-- Asx
SELECT DISTINCT pc1.Hd
FROM pc_uri as pc1, pc_uri as pc2
WHERE pc1.Hd=pc2.hd AND pc1.Cod<>pc2.Cod

-- Asd
SELECT DISTINCT pc1.Model AS Model_1,pc2.Model AS Model_2, pc1.Viteza, pc1.Ram
FROM pc_uri as pc1, pc_uri as pc2
WHERE pc1.Viteza=pc2.Viteza AND
pc1.Ram=pc2.Ram AND 
pc1.Model<>pc2.Model AND
pc1.Cod<pc2.Cod

-- Asdac 
SELECT DISTINCT Tip,produse.Model,Viteza
FROM laptop_uri,produse
WHERE produse.Model=laptop_uri.model AND laptop_uri.Viteza<(
SELECT MIN(Viteza)
FROM pc_uri
) 
Asc
SELECT producator,produse.Model,pret
FROM produse,laptop_uri
WHERE produse.Model=laptop_uri.Model AND Pret=(
SELECT MAX(Pret)
FROM laptop_uri)

UNION

SELECT producator,produse.Model,pret
FROM produse,pc_uri
WHERE produse.Model=pc_uri.Model AND Pret=(
SELECT MAX(Pret)
FROM pc_uri)

-- Azs
SELECT p1.producator,AVG(ecran) AS dimensiuni
FROM laptop_uri,produse AS p1, produse AS p2
WHERE p1.Producator=p2.Producator AND laptop_uri.Model=p1.Model
GROUP BY p1.Producator

-- Asx
SELECT Producator, COUNT(pc_uri.Model)
FROM produse,pc_uri
WHERE produse.Model=pc_uri.Model
GROUP BY produse.Producator
HAVING COUNT(pc_uri.Model)>=3



-- Asd

SELECT Producator, MAX(pc_uri.Pret)
FROM produse,pc_uri
WHERE produse.Model=pc_uri.Model
GROUP BY produse.Producator



-- Asda
SELECT Viteza, AVG(Pret) AS Pret_mediu
FROM pc_uri
WHERE Viteza IN (
SELECT DISTINCT Viteza
FROM pc_uri
WHERE Viteza>600)
GROUP BY Viteza

-- Asd
SELECT DISTINCT producator
FROM produse, pc_uri
WHERE produse.Model=pc_uri.Model AND pc_uri.Viteza>=750

INTERSECT

SELECT DISTINCT producator
FROM produse, laptop_uri
WHERE produse.Model=laptop_uri.Model AND laptop_uri.Viteza>=750

-- Ad
SELECT SUM(DISTINCT Pret)
FROM imprimante
WHERE Pret in (
SELECT MIN(i1.Pret)
FROM imprimante as i1, imprimante as i2
WHERE i1.Tip=i2.Tip
GROUP BY i1.Tip)
As
SELECT produse.Model
FROM produse,pc_uri,imprimante,laptop_uri
WHERE produse.Model=pc_uri.Model AND
pc_uri.Pret>= ALL(SELECT Pret FROM pc_uri) AND
pc_uri.Pret>= ALL(SELECT Pret FROM imprimante) AND
pc_uri.Pret>= ALL(SELECT Pret FROM laptop_uri)

UNION

SELECT produse.Model
FROM produse,pc_uri,imprimante,laptop_uri
WHERE produse.Model=laptop_uri.Model AND
laptop_uri.Pret>= ALL(SELECT Pret FROM pc_uri) AND
laptop_uri.Pret>= ALL(SELECT Pret FROM imprimante) AND
laptop_uri.Pret>= ALL(SELECT Pret FROM laptop_uri)

UNION

SELECT produse.Model
FROM produse,pc_uri,imprimante,laptop_uri
WHERE produse.Model=imprimante.Model AND
imprimante.Pret>= ALL(SELECT Pret FROM pc_uri) AND
imprimante.Pret>= ALL(SELECT Pret FROM imprimante) AND
imprimante.Pret>= ALL(SELECT Pret FROM laptop_uri)




-- Asda
SELECT producator
FROM produse,pc_uri
WHERE produse.Model=pc_uri.Model AND 
pc_uri.Ram IN (SELECT MIN(Ram) FROM pc_uri)

INTERSECT

SELECT Producator
FROM produse
WHERE produse.Tip='Imprimante'
As
SELECT SUM(A.Suma)/SUM(A.Numar)
FROM(
SELECT SUM(Pret) AS Suma, COUNT(Pret) as Numar
FROM pc_uri,produse
WHERE pc_uri.Model=produse.Model AND produse.Producator='A'

UNION 

SELECT SUM(Pret) AS Suma, COUNT(Pret) as Numar
FROM laptop_uri,produse
WHERE laptop_uri.Model=produse.Model AND produse.Producator='A') AS A

-- Asd
SELECT Producator,AVG(pc_uri.Pret) AS Pret_med_prod
FROM pc_uri,produse
WHERE pc_uri.Model=produse.Model AND produse.Producator IN
(SELECT DISTINCT Producator FROM produse WHERE produse.Tip='Imprimante')
GROUP BY Producator

-- Asd
SELECT AVG(pc_uri.Hd) AS HD_med
FROM pc_uri,produse
WHERE pc_uri.Model=produse.Model AND produse.Producator IN
(SELECT DISTINCT Producator FROM produse WHERE produse.Tip='Imprimante')
-- Sd


