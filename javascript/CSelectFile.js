class CSelectFile
{
	static Instance()
	{
		return CSelectFile.m_nInstance;
	}

	constructor()
	{
		this.m_szNodeIDName = "CFileInputNode";
		this.m_pElement = document.getElementById( this.m_szNodeIDName );
		if( !this.m_pElement )
		{
			this.m_pElement = document.createElement( "input" );
			this.m_pElement.type = "file";
			this.m_pElement.id = this.szNodeIDName;
			this.m_pElement.style = "display:none";
			this.m_pElement.onchange = function()
			{
				CSelectFile.Instance()._OnChange();
			};
			document.getElementsByTagName("body")[0].appendChild( this.m_pElement );
		}
		console.log( this.m_szNodeIDName );
	}

	_OnChange()
	{
		var pSelectedFile = this.m_pElement.files[0];
		this.m_szFileName = pSelectedFile.name;
		this.m_nFileSize = pSelectedFile.size;
		var reader = new FileReader();
		reader.readAsText( selectedFile );
		reader.onload = function()
		{
			CSelectFile.Instance()._OnFildLoad( this.result );
		};
	}

	_OnFildLoad( data )
	{
		this.OnCallback( this.m_szFileName, this.m_nFileSize, data );
	}

	OpenFile( func )
	{
		this.OnCallback = func;
		this.m_pElement.click();
	}
}
CSelectFile.m_nInstance = new CSelectFile;

/*
	var aa = CFile.Instance();
	aa.OpenFile( function( name, size, data )
	{
		console.log("文件名:"+name+"大小："+size);
		console.log(data);
	} );
*/