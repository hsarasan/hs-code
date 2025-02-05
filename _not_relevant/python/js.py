import json
from pathlib import Path

class ToJsonMixin:
    def __init__(self, *args, **kwargs):
        for key, value in kwargs.items():
            setattr(self, key, value)
        
    def to_json(self):
        return json.dumps(self.__dict__)
    
path=Path("temp.txt")
path.write_text(ToJsonMixin(name="abc",age=20).to_json())

    
