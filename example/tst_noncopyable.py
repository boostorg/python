import noncopyable_export
import noncopyable_import
s1 = noncopyable_export.store(1)
print s1.recall()
s2 = noncopyable_export.store(2)
print s2.recall()
s3 = noncopyable_import.add_stores(s1, s2)
print s3.recall()
