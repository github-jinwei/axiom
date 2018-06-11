use std::hash::{Hash, Hasher};
use std::marker::PhantomData;
use std::cmp::Ordering;
use mir::MIRContext;

#[derive(Debug, Clone)]
pub struct PoolId<T> {
    id: u64,
    debug_name: String,
    phantom: PhantomData<T>
}

impl<T> PartialEq for PoolId<T> {
    fn eq(&self, other: &PoolId<T>) -> bool {
        self.id == other.id
    }
}

impl<T> Eq for PoolId<T> {}

impl<T> Ord for PoolId<T> {
    fn cmp(&self, other: &PoolId<T>) -> Ordering {
        self.id.cmp(&other.id)
    }
}

impl<T> PartialOrd for PoolId<T> {
    fn partial_cmp(&self, other: &PoolId<T>) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl<T> Hash for PoolId<T> {
    fn hash<H: Hasher>(&self, state: &mut H) {
        self.id.hash(state);
    }
}

impl<T> PoolId<T> {
    pub fn new(debug_name: String, context: &mut MIRContext) -> PoolId<T> {
        PoolId {
            id: context.alloc_id(),
            debug_name,
            phantom: PhantomData
        }
    }

    pub fn get_id(&self) -> u64 {
        self.id
    }

    pub fn get_debug_name(&self) -> &str {
        &self.debug_name
    }
}
