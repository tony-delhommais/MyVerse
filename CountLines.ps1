cd src

$Total = 0

foreach ($file in (Get-ChildItem -Recurse -Include *.h, *.cpp -File))
{
	$Total = $Total + ((get-content $file).count)
}

Write-Host "Total lines of code: $Total"
Write-Host
Write-Host 'Press any key to continue...'
$null = $Host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown')