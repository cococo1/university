-- Sa se suprime baza de date calculatoare creata in lucrarile 3-4:
  DROP DATABASE calculatoare
  
-- Sa se creeze baza de date calculatoare 	(tabele, constringerile de integritate), utilizand limbajul Transact SQL;
 CREATE DATABASE calculatoare 
GO
USE calculatoare

CREATE TABLE produse1(Producator CHAR(1) NOT NULL,Model VARCHAR(4) NOT NULL, Tip VARCHAR(10) NOT NULL)
CREATE UNIQUE INDEX ind_model ON produse1(Model ASC)

CREATE TABLE pc_uri1 (Cod INT NOT NULL IDENTITY(1,1), Model VARCHAR(4) NOT NULL, Viteza DECIMAL(3,0) NOT NULL,
Ram DECIMAL(3,0) NOT NULL, Hd DECIMAL(2,0) NOT NULL, Cd VARCHAR(3) NOT NULL, Pret FLOAT NOT NULL)
CREATE UNIQUE INDEX ind_cod ON pc_uri1(Cod ASC)

CREATE TABLE laptop_uri1 (Cod INT NOT NULL IDENTITY(1,1), Model VARCHAR(4) NOT NULL, Viteza DECIMAL(3,0) NOT NULL,
Ram DECIMAL(3,0) NOT NULL, Hd DECIMAL(2,0) NOT NULL, Pret FLOAT NOT NULL, Ecran INT NOT NULL)
CREATE UNIQUE INDEX ind_cod ON laptop_uri1(Cod ASC)

CREATE TABLE imprimante1 (Cod INT NOT NULL IDENTITY(1,1), Model VARCHAR(4) NOT NULL, Color char(2) NOT NULL, 
Tip VARCHAR(6), Pret FLOAT NOT NULL)
CREATE UNIQUE INDEX ind_cod ON imprimante1(Cod ASC)


SELECT * FROM produse1;
SELECT * FROM pc_uri1;
SELECT * FROM laptop_uri1;
SELECT * FROM imprimante1;   

-- Sa se creeze tabelul 	imprimante_stoc 	cu aceeasi structura ca si a tabelului imprimante. Sa se insereze toate datele din tabelul imprimante in tabelul imprimante_stoc. Sa se scrie, cu acest scop, un numar minimal de instructiuni. 
SELECT * INTO Imprimante_stoc FROM imprimante

-- Adaugati in tabelul produse urmatoarele produse de la producatorul Z: modelul imprimanta-4003, modelul pc-4001, modelul laptop-4002. Sa se scrie o singura instructiune SQL;
 INSERT produse VALUES('Z','4003','Imprimante'),('Z','4001','PC'),('Z','4002','Laptop_uri')

-- Adaugati in tabelul pc_uri modelul 4444 cu codul 22, care are viteza procesorului 1200 si pretul 1350. Caracteristicile care lipsesc trebuie sa fie completate cu valorile implicite definite pentru coloanele respective. Pentru realizarea sarcinii cu succes, daca este necesar, inainte de inserarea datelor, sa se modifice schema tabelului, utilizand instructiunile DDL respective;
 ALTER TABLE pc_uri ALTER COLUMN Viteza DECIMAL(4,0) NOT NULL
ALTER TABLE pc_uri ADD DEFAULT (0) FOR Ram;
ALTER TABLE pc_uri ADD DEFAULT (0) FOR Hd;
ALTER TABLE pc_uri ADD DEFAULT '0x' FOR Cd;
INSERT pc_uri VALUES(22,'4444',1200,DEFAULT,DEFAULT,DEFAULT,1350)

-- Pentru fiecare model de laptopuri,  sa se adauge o inregistrare in tabelul pc_uri cu urmatoarele caracteristici:
-- Cod: codul minimal al laptopului in grup +30;
-- Model: numarul de model al laptopului +100;
-- Viteza: viteza maximala a laptopului in grup;
-- Ram: capacitate maximala a memoriei operative a laptopului in grup *2;
-- Hd: capacitatea maximala a discului dur al laptopului in grup *2;
-- Cd: valoarea implicita;
-- Pret: pretul maximal al laptopului in grup, micsorat de 1.5 ori.

INSERT pc_uri (Cod,Model,Viteza,Ram,Hd,Pret)
(SELECT MIN(Cod)+30 As Cod,Model,MAX(Viteza) AS Viteza, MAX(Ram)*2 AS Ram,MAX(Hd)*2 AS Hd,MAX(Pret)/1.5 AS Pret
FROM laptop_uri	
GROUP BY Model)
-- Sa se scrie interogari de creare a indecsilor asupra tabelelor din baza de date calculatoare pentru a asigura o performanta sporita la executarea interogarilor SELECT din Lucrarea practica 4.

IF EXISTS(SELECT name FROM sys.indexes WHERE name='ind_produse1')
DROP INDEX ind_produse1 ON produse;
GO
CREATE NONCLUSTERED INDEX ind_produse1 ON produse(Producator ASC,Model,Tip)
GO
IF EXISTS(SELECT name FROM sys.indexes WHERE name='ind_produse2')
DROP INDEX ind_produse2 ON produse;
GO
CREATE UNIQUE CLUSTERED INDEX ind_produse2 ON produse(Model ASC)
GO



IF EXISTS(SELECT name FROM sys.indexes WHERE name='ind_pc_uri1')
DROP INDEX ind_pc_uri1 ON pc_uri;
GO
CREATE NONCLUSTERED INDEX ind_pc_uri1 ON pc_uri(Cod ASC,Model,Viteza,Ram,Hd,Cd,Pret)
GO
IF EXISTS(SELECT name FROM sys.indexes WHERE name='ind_pc_uri2')
DROP INDEX ind_pc_uri2 ON pc_uri;
GO
CREATE UNIQUE CLUSTERED INDEX ind_pc_uri2 ON pc_uri(Cod ASC)
GO



IF EXISTS(SELECT name FROM sys.indexes WHERE name='ind_laptop_uri1')
DROP INDEX ind_laptop_uri1 ON laptop_uri;
GO
CREATE NONCLUSTERED INDEX ind_laptop_uri1 ON laptop_uri(Cod ASC,Model,Viteza,Ram,Hd,Pret,Ecran)
GO
IF EXISTS(SELECT name FROM sys.indexes WHERE name='ind_laptop_uri2')
DROP INDEX ind_laptop_uri2 ON laptop_uri;
GO
CREATE UNIQUE CLUSTERED INDEX ind_laptop_uri2 ON laptop_uri(Cod ASC)
GO



IF EXISTS(SELECT name FROM sys.indexes WHERE name='ind_imprimante1')
DROP INDEX ind_imprimante1 ON imprimante;
GO
CREATE NONCLUSTERED INDEX ind_imprimante1 ON imprimante(Cod ASC,Model,Color,Tip,Pret)
GO
IF EXISTS(SELECT name FROM sys.indexes WHERE name='ind_imprimante2')
DROP INDEX ind_imprimante2 ON imprimante;
GO
CREATE UNIQUE CLUSTERED INDEX ind_imprimante2 ON imprimante(Cod ASC)
GO