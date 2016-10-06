option explicit
dim wi, basedb, newdb
const msiTransformValidationLanguage = 1
const msiTransformErrorNone = 0
set wi = CreateObject("WindowsInstaller.Installer")
set basedb = wi.opendatabase("trynotepad.msi", 0)
set newdb = wi.opendatabase ("modifiednotepad.msi", 0)
newdb.GenerateTransform basedb, "thetransform.mst"
newdb.CreateTransformSummaryInfo basedb, "thetransform.mst",_
    msiTransformErrorNone, msiTransformValidationLanguage 
set wi=Nothing