rm -rf "export/Assignment99/*"

cp -r src "export/Assignment99"
cp .classpath "export/Assignment99"
cp .project "export/Assignment99"

cp *.txt "export/Assignment99"

zip -r "Assignment99.zip" export/*
exit