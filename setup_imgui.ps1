#!/usr/bin/env pwsh
# ImGui Setup Script for Windows

Write-Host "================================" -ForegroundColor Cyan
Write-Host "Employee Efficiency Tracker" -ForegroundColor Cyan
Write-Host "Modern UI Setup - ImGui + OpenGL" -ForegroundColor Cyan
Write-Host "================================" -ForegroundColor Cyan
Write-Host ""

# Check if Git is installed
$gitExists = Get-Command git -ErrorAction SilentlyContinue
if (-not $gitExists) {
    Write-Host "❌ Git is not installed. Please install Git first." -ForegroundColor Red
    exit 1
}

# Check if curl is available
$curlExists = Get-Command curl -ErrorAction SilentlyContinue
if (-not $curlExists) {
    Write-Host "❌ curl is not available. Please install it first." -ForegroundColor Red
    exit 1
}

# Download ImGui
Write-Host "📥 Downloading ImGui library..." -ForegroundColor Yellow
if (Test-Path "imgui") {
    Write-Host "ℹ️  ImGui directory already exists. Skipping download." -ForegroundColor Yellow
} else {
    $imgguiZip = "imgui.zip"
    $imgguiVersion = "v1.89.7"
    
    Write-Host "   Downloading ImGui $imgguiVersion..." -ForegroundColor Gray
    Invoke-WebRequest -Uri "https://github.com/ocornut/imgui/archive/refs/tags/$imgguiVersion.zip" `
        -OutFile $imgguiZip `
        -ErrorAction Stop
    
    Write-Host "   Extracting ImGui..." -ForegroundColor Gray
    Expand-Archive -Path $imgguiZip -DestinationPath . -Force
    
    # Move extracted folder to 'imgui'
    $extractedDir = "imgui-1.89.7"
    if (Test-Path $extractedDir) {
        Rename-Item $extractedDir -NewName "imgui" -Force
    }
    
    # Cleanup
    Remove-Item $imgguiZip -Force
    
    Write-Host "✓ ImGui downloaded and extracted successfully!" -ForegroundColor Green
}

Write-Host ""
Write-Host "📦 Checking for required dependencies..." -ForegroundColor Yellow

# Check if GLFW is installed (via MinGW package manager)
$glfwExists = Get-Command pkg-config -ErrorAction SilentlyContinue
if ($glfwExists) {
    $glfwCheck = & pkg-config --exists glfw3 2>$null
    if ($LASTEXITCODE -ne 0) {
        Write-Host "⚠️  GLFW3 not found via pkg-config" -ForegroundColor Yellow
        Write-Host "   You may need to install: mingw-w64-x86_64-glfw" -ForegroundColor Gray
    } else {
        Write-Host "✓ GLFW3 found" -ForegroundColor Green
    }
}

Write-Host ""
Write-Host "✅ Setup completed!" -ForegroundColor Green
Write-Host ""
Write-Host "Next steps:" -ForegroundColor Cyan
Write-Host "1. Install GLFW and OpenGL development libraries (if not already installed)"
Write-Host "2. Run: make setup-imgui (if needed)"
Write-Host "3. Run: make all (to build the project)"
Write-Host "4. Run: .\efficiency_tracker.exe (to launch the application)"
Write-Host ""

Write-Host "📚 For MinGW users, install GLFW via:" -ForegroundColor Yellow
Write-Host "   pacman -S mingw-w64-x86_64-glfw" -ForegroundColor Gray
Write-Host ""
