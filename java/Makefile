HAVERSINE_CLASS := Haversine.class Geotranslation.class LatLong.class
TRANSLATE2D_CLASS := Translate2d.class Geotranslation.class LatLong.class
TRANSLATE3D_CLASS := Translate3d.class Geotranslation.class LatLong.class

HAVERSINE_MANIFEST := haversine-manifest.txt
TRANSLATE2D_MANIFEST := translate2d-manifest.txt
TRANSLATE3D_MANIFEST := translate3d-manifest.txt

HAVERSINE_JAR := Haversine.jar
TRANSLATE2D_JAR := Translate2d.jar
TRANSLATE3D_JAR := Translate3d.jar

# tell make what files we care about
.SUFFIXES: .java .class

# tell make how to associate .java and .class files
.java.class:
	javac $<


all: haversine translate2d translate3d

haversine: $(HAVERSINE_CLASS) $(HAVERSINE_MANIFEST)
	jar -cvfm $(HAVERSINE_JAR) $(HAVERSINE_MANIFEST) $(HAVERSINE_CLASS)

translate2d: $(TRANSLATE2D_CLASS) $(TRANSLATE3D_MANIFEST)
	jar -cvfm $(TRANSLATE2D_JAR) $(TRANSLATE2D_MANIFEST) translate2d-manifest.txt $(TRANSLATE2D_CLASS)

translate3d: $(TRANSLATE3D_CLASS) $(TRANSLATE3D_MANIFEST)
	jar -cvfm $(TRANSLATE3D_JAR) $(TRANSLATE3D_MANIFEST) $(TRANSLATE3D_CLASS)

clean-class:
	rm *.class

clean:
	rm *.jar *.class
