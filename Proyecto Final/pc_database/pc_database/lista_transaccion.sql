CREATE TABLE [dbo].[lista_transaccion]
(
	[id_lista_transaccion] INT NOT NULL PRIMARY KEY IDENTITY, 
    [origen] VARCHAR(5) NULL, 
    [destino] VARCHAR(5) NULL
)
