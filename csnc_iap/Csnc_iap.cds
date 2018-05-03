<distribution version="17.0.0" name="Csnc_iap" type="MSI">
	<prebuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></prebuild>
	<postbuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></postbuild>
	<msi GUID="{2C50DEC5-3B40-46CE-8A3C-B49292AF7900}">
		<general appName="Csnc_iap" outputLocation="f:\cvi\project\CSNC\csnc_iap\cvidistkit.Csnc_iap" relOutputLocation="cvidistkit.Csnc_iap" outputLocationWithVars="f:\cvi\project\CSNC\csnc_iap\cvidistkit.%name" relOutputLocationWithVars="cvidistkit.%name" upgradeBehavior="1" autoIncrement="true" version="1.0.9">
			<arp company="" companyURL="" supportURL="" contact="" phone="" comments=""/>
			<summary title="" subject="" keyWords="" comments="" author=""/></general>
		<userinterface language="Chinese (Simplified)" showPaths="true" showRuntimeOnly="true" readMe="" license="">
			<dlgstrings welcomeTitle="Csnc_iap" welcomeText=""/></userinterface>
		<dirs appDirID="101">
			<installDir name="[Program Files]" dirID="2" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="[Start&gt;&gt;Programs]" dirID="7" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="Csnc_iap" dirID="100" parentID="7" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="Csnc_iap" dirID="101" parentID="2" isMSIDir="false" visible="true" unlock="false"/></dirs>
		<files>
			<simpleFile fileID="0" sourcePath="f:\cvi\project\CSNC\csnc_iap\cvibuild.csnc_iap\Release\app_iap.exe" targetDir="101" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="1" sourcePath="f:\cvi\project\CSNC\csnc_iap\..\opencom\uir\comconfig.uir" relSourcePath="..\opencom\uir\comconfig.uir" relSourceBase="0" targetDir="101" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="2" sourcePath="f:\cvi\project\CSNC\csnc_iap\mian.uir" relSourcePath="mian.uir" relSourceBase="0" targetDir="101" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="3" sourcePath="f:\cvi\project\CSNC\csnc_iap\iap\IAP.uir" relSourcePath="iap\IAP.uir" relSourceBase="0" targetDir="101" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/></files>
		<fileGroups>
			<projectOutput targetType="0" dirID="101" projectID="0">
				<fileID>0</fileID></projectOutput>
			<projectDependencies dirID="101" projectID="0"/></fileGroups>
		<shortcuts>
			<shortcut name="Csnc_iap" targetFileID="0" destDirID="100" cmdLineArgs="" description="" runStyle="NORMAL"/></shortcuts>
		<mergemodules/>
		<products/>
		<runtimeEngine installToAppDir="false" activeXsup="false" analysis="true" cvirte="true" dotnetsup="true" instrsup="true" lowlevelsup="true" lvrt="true" netvarsup="true" rtutilsup="false">
			<hasSoftDeps/>
			<doNotAutoSelect>
			<component>activeXsup</component>
			<component>rtutilsup</component>
			</doNotAutoSelect></runtimeEngine><sxsRuntimeEngine>
			<selected>false</selected>
			<doNotAutoSelect>false</doNotAutoSelect></sxsRuntimeEngine>
		<advanced mediaSize="650">
			<launchConditions>
				<condition>MINOS_WIN7_SP1</condition>
			</launchConditions>
			<includeConfigProducts>true</includeConfigProducts>
			<maxImportVisible>silent</maxImportVisible>
			<maxImportMode>merge</maxImportMode>
			<custMsgFlag>false</custMsgFlag>
			<custMsgPath>msgrte.txt</custMsgPath>
			<signExe>false</signExe>
			<certificate></certificate>
			<signTimeURL></signTimeURL>
			<signDescURL></signDescURL></advanced>
		<baselineProducts>
			<product name="NI Variable Engine 2017" UC="{EB7A3C81-1C0F-4495-8CE5-0A427E4E6285}" productID="{3011FA37-DCC4-4BF8-8900-12D68EC7996F}" path="(None)" flavorID="DefaultFull" flavorName="Full" verRestr="false" coreVer="17.0.49152">
				<dependencies>
					<productID>{17349EEB-C92B-4E22-9BC0-C6D5CD6E380C}</productID>
					<productID>{26B72B11-2EF9-4F28-9D4B-9ABD3E854149}</productID>
					<productID>{48DC4AF0-9266-40CE-9E9F-D0EE43FE31DE}</productID>
					<productID>{5691A0DE-3987-4595-A7F8-91133A3C1437}</productID>
					<productID>{5F956678-03F3-4CF5-88C4-78E8181E2081}</productID>
					<productID>{5FE7B722-6061-4AFA-A26F-2979CB4FEA40}</productID>
					<productID>{68428815-FD93-4897-BC4A-EC5E3194C4E7}</productID>
					<productID>{6EF29D99-5FE4-4D63-87DE-0644222061A2}</productID>
					<productID>{78C76251-4DA2-4142-9C57-933B559F6E18}</productID>
					<productID>{9A1C4805-EB50-44F1-87C7-29F5574B44E4}</productID>
					<productID>{DA09F5A1-AA07-467D-A0B5-31D9EC8B5048}</productID>
					<productID>{DDFE3456-19AC-42FC-92C1-CFC10E43A97D}</productID>
					<productID>{F05EC50F-B2B4-4B87-A32C-6F9AD11D1B49}</productID>
					<productID>{FE7D71A2-BF64-441C-9489-BE6F6937B98E}</productID></dependencies></product>
			<product name="NI LabWindows/CVI Shared Runtime 2017" UC="{80D3D303-75B9-4607-9312-E5FC68E5BFD2}" productID="{28BFBCB6-5EEE-47F1-A894-FCD877057827}" path="(None)" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="17.0.49157">
				<dependencies>
					<productID>{13774AE4-124D-48C2-A8AC-F8070918385E}</productID>
					<productID>{17349EEB-C92B-4E22-9BC0-C6D5CD6E380C}</productID>
					<productID>{18C5DCAB-EF32-48F8-9789-2A33DE1CA2CB}</productID>
					<productID>{29FBD1D9-6A19-4CF6-935F-C0EFCFB6CA3D}</productID>
					<productID>{2D894BCB-6069-418C-BF94-8E5915D8867C}</productID>
					<productID>{2FC99AB8-F11D-4938-B14F-AC60D1016FE7}</productID>
					<productID>{35E63DC2-6BCC-48D6-A1C5-5B068DF34117}</productID>
					<productID>{48DC4AF0-9266-40CE-9E9F-D0EE43FE31DE}</productID>
					<productID>{4A548403-7448-4B6D-8A8E-F41F53AE4A3F}</productID>
					<productID>{5691A0DE-3987-4595-A7F8-91133A3C1437}</productID>
					<productID>{5E99102B-D07A-4D85-8D50-4BE55E3633A0}</productID>
					<productID>{5F956678-03F3-4CF5-88C4-78E8181E2081}</productID>
					<productID>{5FE7B722-6061-4AFA-A26F-2979CB4FEA40}</productID>
					<productID>{68428815-FD93-4897-BC4A-EC5E3194C4E7}</productID>
					<productID>{6EF29D99-5FE4-4D63-87DE-0644222061A2}</productID>
					<productID>{A4FAF873-938B-43B8-BBF2-E4B2C0CE730B}</productID>
					<productID>{BEA1952D-1F00-4336-9A76-C41FA181C02D}</productID>
					<productID>{CE7D38A4-66ED-4D33-A385-D4A2CF4BFF81}</productID>
					<productID>{D357A74D-E186-4E4B-AF78-E035D3E83368}</productID>
					<productID>{D4E86102-76C1-458C-B0C2-F42B43CAD3CC}</productID>
					<productID>{DA09F5A1-AA07-467D-A0B5-31D9EC8B5048}</productID>
					<productID>{DBAAC357-96E7-459F-B115-B14E29F652EF}</productID>
					<productID>{E2821E0B-CB08-41BD-AE01-A9068F7B8771}</productID>
					<productID>{F05EC50F-B2B4-4B87-A32C-6F9AD11D1B49}</productID>
					<productID>{FE7D71A2-BF64-441C-9489-BE6F6937B98E}</productID>
					<productID>{FF35E2A2-9214-4B76-91AE-5567076AAE8C}</productID>
					<productID>{FF56A0C1-3413-4024-89A6-0FB565B2E78C}</productID></dependencies></product></baselineProducts>
		<Projects NumProjects="1">
			<Project000 ProjectID="0" ProjectAbsolutePath="f:\cvi\project\CSNC\csnc_iap\csnc_iap.prj" ProjectRelativePath="csnc_iap.prj"/></Projects>
		<buildData progressBarRate="3.247601172238637">
			<progressTimes>
				<Begin>0.000000000000000</Begin>
				<ProductsAdded>0.125749398437479</ProductsAdded>
				<DPConfigured>0.588286328124927</DPConfigured>
				<DPMergeModulesAdded>1.076667845703145</DPMergeModulesAdded>
				<DPClosed>2.275396097656214</DPClosed>
				<DistributionsCopied>2.450118882812534</DistributionsCopied>
				<End>30.791958339843802</End></progressTimes></buildData>
	</msi>
</distribution>
